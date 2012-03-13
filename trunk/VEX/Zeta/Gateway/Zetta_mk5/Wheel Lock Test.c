#pragma config(Sensor, dgtl1,  EncFL,               sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  EncBL,               sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  EncBR,               sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  EncFR,               sensorQuadEncoder)
#pragma config(Motor,  port2,           FrontLeft1,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           FrontLeft2,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           BackLeft,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           BackRight,     tmotorNormal, openLoop)
#pragma config(Motor,  port8,           FrontRight1,   tmotorNormal, openLoop)
#pragma config(Motor,  port9,           FrontRight2,   tmotorNormal, openLoop)

task main {
  while (true){
SensorValue[EncBL] = 0;
    // Basic Lock Wheel Test NEEDS PID
    if (-15 < vexRT[Ch3] < 15 ) {

      if (SensorValue[EncBL] > 0) {
        motor[BackLeft] = 127;
      }
      else if (SensorValue[EncBL] < 0) {
        motor[BackLeft] = -127;
      }
      else {
        motor[BackLeft] = -127;
    }
  }
  else {//normal drive
    motor[BackLeft] = vexRT[Ch3];
  }
}//while
}//task
