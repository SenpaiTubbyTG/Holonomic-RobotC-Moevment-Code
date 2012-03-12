/*		Written by Aaron Osmer, 2009, ajosmer@gmail.com		*/
/*					May be distributed freely.				*/

#include "holodrive.h"

short squarejoy(short joyval) {
	int intjoyval;
	joyval -= 127;
	intjoyval = (int)(joyval * joyval);
	if(joyval<0) intjoyval *= -1;
	intjoyval /= 128;
//	printf("squarejoy(%hd) = %ld\r", joyval+127, intjoyval);
	return (short) intjoyval+127;
}

short charabs(short x) {
	x-=127;	//Subtracts 127 from the value
	if(x<0)return -x; //Return the negative of a negative
	else return x;	//Return the positive of a positive
}

void holodrive(short forward, short side, short rotate, unsigned char square, unsigned char FL, unsigned char FR, unsigned char BL, unsigned char BR) {

	//forward is the forward input value, side is the sideways input value, and rotate is the rotate input value.  FL = front left, FR = front right, BL = back left, BR = back right.  square is a boolean value that tells whether or not to square the input values to give you more precision at low values, but still max speed.

	short wheel[4], lim=0;  //FL,FR,BL,BR
	unsigned char i; //Used as the counter in the for() loops

	if(square) {	//Take input value and use a quadratic function to increase low-speed sensitivity if specified.
		forward = squarejoy(forward);
		side = squarejoy(side);
		rotate = squarejoy(rotate);
	}


/*Drive equations, sets lim to the highest wheel magnitude.  Single "=" sets the wheel value*/
	if(charabs(wheel[0] = (forward + (side - 127) + (rotate - 127))) > lim) lim=charabs(wheel[0]);
	if(charabs(wheel[1] = ((254 - forward) + (side - 127) + (rotate - 127))) > lim) lim=charabs(wheel[1]);
	if(charabs(wheel[2] = (forward - (side - 127) + (rotate - 127))) > lim) lim=charabs(wheel[2]);
	if(charabs(wheel[3] = ((254 - forward) - (side - 127) + (rotate - 127))) > lim) lim=charabs(wheel[3]);

	//If lim is out of the acceptable range, scale all wheels to the most out-of-range wheel.  See charabs().  Separated into steps because of an error in the compiler that only allows one mathematical operator per line in some instances.
	if(lim>=127) for(i=0; i<4; i++) {
		wheel[i] -= 127;
		wheel[i] *= 127;
		wheel[i] /= lim;
		wheel[i] += 127;
	}

	//Drive the motors.  Casts explicitly from a short to an unsigned character.
	SetPWM(FL, (unsigned char)wheel[0]);
	SetPWM(FR, (unsigned char)wheel[1]);
	SetPWM(BL, (unsigned char)wheel[2]);
	SetPWM(BR, (unsigned char)wheel[3]);
}
