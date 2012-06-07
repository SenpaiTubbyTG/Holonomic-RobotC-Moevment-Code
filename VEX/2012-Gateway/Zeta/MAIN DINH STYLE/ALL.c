#pragma config(UART_Usage, UART2, VEX_2x16_LCD, baudRate19200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  nick,           sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  startAuton,     sensorTouch)
#pragma config(Sensor, dgtl7,  encoderL,       sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  solenoidL,      sensorDigitalOut)
#pragma config(Sensor, dgtl10, solenoidR,      sensorDigitalOut)
#pragma config(Sensor, dgtl11, encoderR,       sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           collectorL,    tmotorServoContinuousRotation, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port2,           frontL,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           frontL2,       tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           backL,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           backL2,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           frontR,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           frontR2,       tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           backR,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           backR2,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port10,          collectorR,    tmotorServoContinuousRotation, openLoop, encoder, encoderPort, I2C_2, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
short count = 0;
bool Iso = false;
bool on  = false;
bool red = false;
bool Program = false;
bool color = false;
char programselect = 0;//save space
bool stall = false;
short Isolation_RED_Program = 0;
short Interaction_RED_Program = 0;
short Isolation_BLUE_Program = 0;
short Interaction_BLUE_Program = 0;

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

void waitForPress()  {
  while(nLCDButtons == 0)  {
    wait1Msec(5);
  }
}

void waitForRelease()  {
  while(nLCDButtons != 0) {
    wait1Msec(5);
  }
}

void menuTracker()  {
  if(nLCDButtons == leftButton)  {
    waitForRelease();
    count--;
  }
  else if(nLCDButtons == rightButton)  {
    waitForRelease();
    count++;
  }
}

void clearLCD()  {
  clearLCDLine(1);
  clearLCDLine(0);

}

void LCDER(string here)  {
  clearLCDLine(1);
  bLCDBacklight = true;
  displayLCDPos(1,11);
  displayNextLCDString(here);
}

void clearwhichline(char line)  {
clearLCDLine(line);
}

void RobotReady()  {

  clearLCDLine(0);
  clearLCDLine(1);
  displayLCDPos(0,0);
  displayNextLCDString("Robot ready");
  wait1Msec(300);
  displayNextLCDString(".");
  wait1Msec(300);
  displayNextLCDString(".");
  wait1Msec(300);
  displayNextLCDString(".");
  wait1Msec(500);
  bLCDBacklight = false;
}

void setSuckSpeed(int speed, int duration)   {
  motor[collectorL] = motor[collectorR] = speed;
  wait1Msec(duration);
  motor[collectorL] = motor[collectorR] = 0;
}//END void

void drive_forward_msec(int speed, int duration) {
  motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = speed;
  wait1Msec(duration);
  motor[frontL] = motor[frontL2] = motor[backL] = motor[backL2] = motor[frontR] = motor[frontR2] = motor[backR] = motor[backR2] = 0;
}//END void

void pre_auton() {
  bStopTasksBetweenModes = true;

  bLCDBacklight = true;
  displayLCDPos(0,0);
  displayNextLCDString("program select");
  redteam = true;
  screenrefresh();
  time1[T1] = 0;
  while (programselecting == true)  {

    if (nLCDButtons & kButtonLeft)  {

      while (nLCDButtons & kButtonLeft)  {
      }
      if (redteam == true)  {
        redteam = false;
      }
      else if (redteam == false)  {
        redteam = true;
      }
      screenrefresh();
    }// end while
    if (nLCDButtons & kButtonCenter)  {
      while (nLCDButtons & kButtonCenter)
      {
      }
      programselect = programselect+1;
      if (programselect > totalprogramnumber)
      {
        programselect = 1;
      }
      screenrefresh();
    }
    if (nLCDButtons & kButtonRight)
    {
      clearLCDLine(0);
      clearLCDLine(1);
      displayLCDPos(0,0);
      displayNextLCDString("Robot ready");
      wait1Msec(300);
      displayNextLCDString(".");
      wait1Msec(300);
      displayNextLCDString(".");
      wait1Msec(300);
      displayNextLCDString(".");
      wait1Msec(500);
      bLCDBacklight = false;
      programselecting = false;
    }
  }
}//end pre_auton

task autonomous()  {

    if (redteam == true)
    if (programselect == 1)  {
    Red_Program = 1;
  }

    if (redteam == true)
    if (programselect == 2)  {
    Red_Program = 2;
  }

    if (redteam == true)
    if (programselect == 3)  {
    Red_Program = 3;
  }

    if (redteam == false)
    if (programselect == 1)  {
    Blue_Program = 1;
  }

    if (redteam == false)
    if (programselect == 2)  {
    Blue_Program = 2;
  }

    if (redteam == false)
    if (programselect == 3)  {
    Blue_Program = 3;
  }

///////////////////////////////////////////////////////////////////////////////////////////////
  {
    if(Red_Program == 1)
    {
      autonIntHighLow();
    }
    else if(Red_Program ==2)
    {
      autonIntHighLow();
    }
    else if(Red_Program ==3)
    {
      autonIntHighLow();
    }
    else if (Blue_Program ==  1)
    {
      autonIntHighLow();
    }
    else if(Blue_Program == 2)
    {
      autonIntHighLow();
    }
    else if(Blue_Program == 3)
    {
      autonIntHighLow();
    }

  }// end bracket set
}// end task autonomous

task usercontrol()
{
 while (true)
	{
	}//end while loop
}//end task usercontrol
