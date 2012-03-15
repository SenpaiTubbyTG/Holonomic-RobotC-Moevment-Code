#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in8,    Gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  pneu1,          sensorDigitalOut)
#pragma config(Sensor, dgtl2,  pneu2,          sensorDigitalOut)
#pragma config(Sensor, dgtl3,  pneu3,          sensorDigitalOut)
#pragma config(Sensor, dgtl4,  pneu4,          sensorDigitalOut)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           right3,        tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port2,           right1,        tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port3,           right2,        tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port4,           left1,         tmotorVex269, openLoop)
#pragma config(Motor,  port5,           left2,         tmotorVex269, openLoop)
#pragma config(Motor,  port10,          left3,         tmotorVex393, openLoop, encoder, encoderPort, I2C_2, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "Variables.c"
#include "Gyrolib.c"
#include "Encoderlib.c"






task main()
{
  // clearLCDLine(1);
  // clearLCDLine(0);
  // displayLCDString(0,0, "Inches :");
  // displayLCDNumber(1,0, nMotorEncoder[left3] * 4 / 360 * PI, 6);
  drive_Enc(127,20,100);
}