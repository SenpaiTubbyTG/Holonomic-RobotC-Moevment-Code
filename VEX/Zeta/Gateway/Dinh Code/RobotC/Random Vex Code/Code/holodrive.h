/*		Written by Aaron Osmer, 2009, ajosmer@gmail.com		*/
/*					May be distributed freely.				*/

#ifndef HOLODRIVE_H_
#define HOLODRIVE_H_

//Squaring function for the joystick values
short squarejoy(short joyval);

//Acts as an absolute value function for the zero value 127
short charabs(short x);

//The main holonomic drive function
void holodrive(short forward, short side, short rotate, unsigned char square, unsigned char FL, unsigned char FR, unsigned char BL, unsigned char BR);


#endif  //HOLODRIVE_H_
