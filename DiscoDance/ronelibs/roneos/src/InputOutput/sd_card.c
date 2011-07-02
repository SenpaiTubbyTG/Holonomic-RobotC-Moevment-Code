/**
 * @file sd_card.c
 * Functions that control the sd card.
 */

#include "inc/lm3s8962.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_qei.h"

#include "driverlib/flash.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/qei.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/ssi.h"
#include "driverlib/interrupt.h"

#include "roneos.h"

uint8 timer1, timer2;
uint8 cardType;
uint stat = STA_NOINIT;

/**
 * Transmit a byte to SD via SPI
 */
static void SDCardXmitSPI(uint8 dat) {
	uint32 rcvdat;
	//SPISelectDevice(SPI_SDCARD);
	MAP_SSIDataPut(SSI0_BASE, dat); /* Write the data to the tx fifo */
	MAP_SSIDataGet(SSI0_BASE, &rcvdat); /* flush data read during the write */
	//SPIDeselect();
}

/**
 * Receive a byte from SD via SPI
 */
static uint8 SDCardRcvrSPI(void) {
	uint32 rcvdat;
	//SPISelectDevice(SPI_SDCARD);
	MAP_SSIDataPut(SSI0_BASE, 0xFF); /* Write dummy data */
	MAP_SSIDataGet(SSI0_BASE, &rcvdat); /* read data from rx fifo */
	//SPIDeselect();
	return (uint8) rcvdat;
}

static void SDCardRcvrSPI_m(uint8 *dst) {
	*dst = SDCardRcvrSPI();
}

/**
 * Wait for card ready.
 */
static uint8 SDCardWaitReady(void) {
	uint8 res;
	timer2 = 50; /* Wait for ready in timeout of 500 ms */
	SDCardRcvrSPI();
	do {
		res = SDCardRcvrSPI();
	} while ((res != 0xFF) && timer2);

	return res;
}

/**
 * Receive a data packet from SD card.
 */
static boolean SDCardRcvrDatablock(uint8 *buff, uint16 btr) {
	uint8 token;

	timer1 = 10;
	/* Wait for data packet in timeout of 100 ms */
	do {
		token = SDCardRcvrSPI();
	} while ((token == 0xFF) && timer1);
	if (token != 0xFE) {
		return FALSE; /* If not valid, return with error. */
	}

	/* Receive the data block into buffer. */
	do {
		SDCardRcvrSPI_m(buff++);
		SDCardRcvrSPI_m(buff++);
	} while (btr -= 2);
	SDCardRcvrSPI(); /* Discard CRC */
	SDCardRcvrSPI();

	return TRUE; /* Return with success */
}

/**
 * Sent a data packet to SD card.
 */
static boolean SDCardXmitDatablock(const uint8 *buff, uint8 token) {
	uint8 resp, wc;

	if (SDCardWaitReady() != 0xFF) return FALSE;

	SDCardXmitSPI(token);
	if (token != 0xFD) {
		wc = 0;
		do {
			SDCardXmitSPI(*buff++);
			SDCardXmitSPI(*buff++);
		} while (--wc);
		SDCardXmitSPI(0xFF);
		SDCardXmitSPI(0xFF);
		resp = SDCardRcvrSPI();
		if ((resp & 0x1F) != 0x05) {
			return FALSE;
		}
	}

	return TRUE;
}

/**
 * Send a command packet to SD.
 * @param cmd Command byte
 * @param arg Argument
 */
static uint8 SDCardSendCmd (uint8 cmd, uint32 arg) {
	uint8 n, res;

	if (SDCardWaitReady() != 0xFF) {
		return 0xFF;
	}

	/* Send command packet. */
	SDCardXmitSPI(cmd); // Command
	SDCardXmitSPI((uint8)(arg >> 24)); // arg[31..24]
	SDCardXmitSPI((uint8)(arg >> 16)); // arg[23..16]
	SDCardXmitSPI((uint8)(arg >> 8)); // arg[15..8]
	SDCardXmitSPI((uint8)arg); // arg[7..0]
	n = 0;
	if (cmd == CMD0) { n = 0x95; } // CRC for CMD0 (0)
	if (cmd == CMD8) { n = 0x87; } // CRC for CMD8 (0x1AA)
	SDCardXmitSPI(n);

	// Receive command response
	if (cmd == CMD12) SDCardRcvrSPI(); // Skip a stuff byte when stop reading.
	n = 10; // Wait for a valid response in timeout of 10 attempts
	do {
		res = SDCardRcvrSPI();
	} while ((res & 0x80) && --n);

	return res; // Return with the response value
}

uint8 SDCardSendCmd12 (void) {
	uint8 n, res, val;
	// We don't wait for the card to be idle.
	// Send command packet - the argument is ignored.
	SDCardXmitSPI(CMD12);
	SDCardXmitSPI(0);
	SDCardXmitSPI(0);
	SDCardXmitSPI(0);
	SDCardXmitSPI(0);
	SDCardXmitSPI(0);

	// Read up to 10 bytes from the card, remembering the value read if not 0xFF
	for (n = 0; n < 10; n++) {
		val = SDCardRcvrSPI();
		if (val != 0xFF) {
			res = val;
		}
	}

	return res; // Return with the response value.
}

// FIXME: Should be `SDCardInit`?
uint8 SDCardInit(uint8 drv) {
	uint8 n, ty, ocr[4];

	if (drv) { return STA_NOINIT; } // Supports only single drive
	if (stat & STA_NODISK) { return stat; } // No card in socket

	SPISelectDevice(SPI_SDCARD);
	ty = 0;
	// Enter idle state
	if (SDCardSendCmd(CMD0, 0) == 1) {
		timer1 = 100;
		// SDC Ver2+
		if (SDCardSendCmd(CMD8, 0x1AA) == 1) {
			for (n = 0; n < 4; n++) {
				ocr[n] = SDCardRcvrSPI();
			}
			// The card can work at vdd range of 2.7-3.6V
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) {
				do {
					if (SDCardSendCmd(CMD55, 0) <= 1 && SDCardSendCmd(CMD41, 1UL << 30) == 0) {
						break; // ACMD41 with HCS bit.
					}
				} while (timer1);
				// Check CCS bit.
				if (timer1 && SDCardSendCmd(CMD58, 0) == 0) {
					for (n = 0; n < 4; n++) {
						ocr[n] = SDCardRcvrSPI();
						ty = (ocr[0] & 0x40) ? 6 : 2;
					}
				}
			}
		} else {
			// SDC Ver1 or MMC
			ty = (SDCardSendCmd(CMD55, 0) <= 1 && SDCardSendCmd(CMD41, 0) <= 1) ? 2 : 1; // SDC : MMC
			do {
				if (ty == 2) {
					if (SDCardSendCmd(CMD55, 0) <= 1 && SDCardSendCmd(CMD41, 0) == 0) {break; }
				} else {
					if (SDCardSendCmd(CMD1, 0) == 0) { break; }
				}
			} while (timer1);

			// Select R/W block length
			if (!timer1 || sdcardsendcmd(CMD16, 512) != 0) {
				ty = 0;
			}
		}
		cardType = ty;
		SPIDeselect();
		SDCardRcvrSPI(); // FIXME: But the card is deselected...

		if (ty) {
			stat &= ~STA_NOINIT;
			//TODO: "set_max_speed()"
		} else {
			// TODO: "power_off()"
		}
	}
	return stat;
}

uint8 SDCardStatus(uint8 drv) {
	if (drv) { return STA_NOINIT; }
	return stat;
}

/**
 * @brief Read sector(s).
 * @param drv Physical drive number (0)
 * @param buff Pointer to the data buffer to store read data.
 * @param sector Start sector number (LBA).
 * @param count Sector count (1..255)
 */
uint8 SDCardRead(uint8 drv, uint8 *buff, uint32 sector, uint8 count) {
	if (drv || !count) return RES_PARERR;
	if (stat & STA_NOINIT) return RES_NOTRDY;

	if (!(cardType & 4)) { sector *= 512; } // Convert to byte address if needed

	SPISelectDevice(SPI_SDCARD);

	// Single block read
	if (count == 1) {
		if ((SDCardSendCmd(CMD17, sector) == 0) && SDCardRcvrDatablock(buff, 512)) {
			count = 0;
		}
	} else {
		// Multiple block read
		if (SDCardSendCmd(CMD18, sector) == 0) {
			do {
				if (!rcvr_datablock(buff, 512)) { break; }
				buff += 512;
			} while (--count);
			SDCardSendCmd12(); // stop transmission
		}
	}
	SPIDeselect();
//	SDCardRcvrSPI(); // FIXME: Can you put/get after deselecting?

	return count ? RES_ERROR : RES_OK;
}

/**
 * @brief Write sector(s).
 * @param drv Physical drive number (0).
 * @param buff Pointer to the data to be written
 * @param sector Start sector number (LBA).
 * @param count Sector count (1..255).
 */
uint8 SDCardWrite(uint8 drv, uint8 *buff, uint32 sector, uint8 count) {
	if (drv || !count) { return RES_PARERR; }
	if (stat & STA_NOINIT) { return RES_NOTRDY; }
	if (stat & STA_PROTECT) { return RES_WRPRT; }

	if (!(cardType & 4)) {sector *= 512; } // Convert to byte address if needed.

	SPISelectDevice(SPI_SDCARD);

	if (count == 1) {
		// Single block write
		if ((SDCardSendCmd(CMD24, sector) == 0) && SDCardXmitDatablock(buff, 0xFE)) {
			count = 0;
		}
	} else {
		// Multiple block write
		if (cardType & 2) {
			SDCardSendCmd(CMD55, 0);
			SDCardSendCmd(CMD23, count); // ACMD23
		}
		if (SDCardSendCmd(CMD25, sector) == 0) {
			do {
				if (!SDCardXmitDatablock(buff, 0xFC)) { break; }
				buff += 512;
			} while (--count);
			if (!SDCardXmitDatablock(0xFD)) { count = 1; }
		}
	}

	SPIDeselect();
//	SDCardRcvrSPI(); // FIXME: Can you do this?

	return count ? RES_ERROR : RES_OK;
}
