#ifndef BUMP_SENSOR_H_
#define BUMP_SENSOR_H_

/*	DEFAULT NUMBERING SCHEME STARTS AT FRONT-RIGHT (11 O'CLOCK), INCREASES CCW  */
#define BUMP_0 				0x01		//P2.0, 11 o'clock
#define BUMP_1 				0x02		//P2.1, 10 o'clock
#define BUMP_2 				0x04		//P2.2, 8 o'clock
#define BUMP_3 				0x08		//P2.3, 7 o'clock, "FROBBY BUTTON"???
#define BUMP_4 				0x10		//P2.4, 5 o'clock
#define BUMP_5 				0x20		//P2.5, 4 o'clock
#define BUMP_6 				0x40		//P2.6, 2 o'clock
#define BUMP_7	 			0x80		//P2.7, 1 o'clock

/* ALTERNATE NUMBERING SCHEME STARTS AT FRONT-LEFT (1 O'CLOCK), INCREASES CW */
//#define BUMP0_BIT 			0x80		//P2.7, 1 o'clock
//#define BUMP1_BIT 			0x40		//P2.6, 2 o'clock
//#define BUMP2_BIT 			0x20		//P2.5, 4 o'clock
//#define BUMP3_BIT 			0x10		//P2.4, 5 o'clock
//#define BUMP4_BIT 			0x08		//P2.3, 7 o'clock, "FROBBY BUTTON"???
//#define BUMP5_BIT 			0x04		//P2.2, 8 o'clock
//#define BUMP6_BIT 			0x02		//P2.1, 10 o'clock
//#define BUMP7_BIT 			0x01		//P2.0, 11 o'clock

/* NAMING SCHEME BASED ON CLOCK HANDS */
#define BUMP_1_OCLOCK		0X80		//P2.7
#define BUMP_2_OCLOCK		0X40		//P2.6
#define BUMP_4_OCLOCK		0X20		//P2.5
#define BUMP_5_OCLOCK		0X10		//P2.4
#define BUMP_7_OCLOCK		0X08		//P2.3
#define BUMP_8_OCLOCK		0X04		//P2.2
#define BUMP_10_OCLOCK		0X02		//P2.1
#define BUMP_11_OCLOCK		0X01		//P2.0


void update_bumpers(uint8 new_values);
//uint8 get_bumpers(uint8 bumper);
uint8 get_bumpers();
void bumper_debug_print();

#endif /* BUMP_SENSOR_H_ */
