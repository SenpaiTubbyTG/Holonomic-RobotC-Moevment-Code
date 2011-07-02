#ifndef MSP430_H_
#define MSP430_H_


/**
 * Commands
 */
void msp430Init(void);
void msp430_spi_send_latch(void);
void msp430GetData(uint8 msg);
uint32 msp430_spi_recv();

#endif /* MSP430_H_ */
