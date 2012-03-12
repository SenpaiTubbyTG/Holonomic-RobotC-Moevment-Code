void applydownwardtrim()
{
motor[port3] = -40;
motor[port4] = -40;
motor[port5] = -40;
motor[port6] = -40;
}

void raisetoposition(int armposition2)
{
while(SensorValue[in1] < armposition2)
{

if (armposition2 - SensorValue[in1] >= 40 && armposition2 - SensorValue[in1] <= 128)
{
motor[port3] = armposition2 - SensorValue[in1];
motor[port4] = armposition2 - SensorValue[in1];
motor[port5] = armposition2 - SensorValue[in1];
motor[port6] = armposition2 - SensorValue[in1];
}

if (armposition2 - SensorValue[in1] < 40)
{
motor[port3] = 40;
motor[port4] = 40;
motor[port5] = 40;
motor[port6] = 40;
}

if (armposition2 - SensorValue[in1] > 128)
{
motor[port3] = 128;
motor[port4] = 128;
motor[port5] = 128;
motor[port6] = 128;
}

}

if (SensorValue[in1] < 600)
{
motor[port3] = 20;
motor[port4] = 20;
motor[port5] = 20;
motor[port6] = 20;
}
if (SensorValue[in1] >= 600)
{
motor[port3] = 0;
motor[port4] = 0;
motor[port5] = 0;
motor[port6] = 0;
}

}

task raisearmtoposition()
{
switch(updown)
{
case true:
while(SensorValue[in1] < armposition)
{

if (armposition - SensorValue[in1] >= 40 && armposition - SensorValue[in1] <= 128)
{
motor[port3] = armposition - SensorValue[in1];
motor[port4] = armposition - SensorValue[in1];
motor[port5] = armposition - SensorValue[in1];
motor[port6] = armposition - SensorValue[in1];
}

else if (armposition - SensorValue[in1] < 40)
{
motor[port3] = 40;
motor[port4] = 40;
motor[port5] = 40;
motor[port6] = 40;
}

else if (armposition - SensorValue[in1] > 128)
{
motor[port3] = 128;
motor[port4] = 128;
motor[port5] = 128;
motor[port6] = 128;
}

}
break;

case false:
while(SensorValue[in1] > armposition)
{

if (armposition - SensorValue[in1] >= 40 && armposition - SensorValue[in1] <= 128)
{
motor[port3] = armposition - SensorValue[in1];
motor[port4] = armposition - SensorValue[in1];
motor[port5] = armposition - SensorValue[in1];
motor[port6] = armposition - SensorValue[in1];
}

else if (armposition - SensorValue[in1] < 40)
{
motor[port3] = -40;
motor[port4] = -40;
motor[port5] = -40;
motor[port6] = -40;
}

else if (armposition - SensorValue[in1] > 128)
{
motor[port3] = -128;
motor[port4] = -128;
motor[port5] = -128;
motor[port6] = -128;
}

}
break;
}
if (armposition < 600 && armposition > 100)
{
motor[port3] = 20;
motor[port4] = 20;
motor[port5] = 20;
motor[port6] = 20;
}
if (armposition >= 600)
{
motor[port3] = 0;
motor[port4] = 0;
motor[port5] = 0;
motor[port6] = 0;
}
if (armposition <= 100)
{
motor[port3] = -20;
motor[port4] = -20;
motor[port5] = -20;
motor[port6] = -20;
}
wait1Msec(200);
}


void lowerarm()
{
motor[port3] = -127;
motor[port4] = -127;
motor[port5] = -127;
motor[port6] = -127;
while(SensorValue[in1] > 100)
{
}
motor[port3] = 0;
motor[port4] = 0;
motor[port5] = 0;
motor[port6] = 0;
}

void armdown()
{
	motor[port3] = -127;
	motor[port4] = -127;
	motor[port5] = -127;
	motor[port6] = -127;
}
