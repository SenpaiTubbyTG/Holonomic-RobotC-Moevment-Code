 void stop()
{
motor[port1] = 0;
motor[port2] = 0;
}

void resetencoders()
{
SensorValue[in15] = 0;
SensorValue[in16] = 0;
}

int distance()
{
return SensorValue[in15] + SensorValue[in16];
}

void moveslow(int leftamount, int rightamount)
{
resetencoders();

while (SensorValue[in15] + SensorValue[in16] <= leftamount + rightamount)
{
motor[port1] = 60;
motor[port2] = 60;
}
}



void move(int leftamount, int rightamount)
{

if (leftamount == 0 && rightamount == 0)
{
}

else
{

///////////////////Variables///////////////////////////
int dir;
///////////////////////////////////////////////////////

if (leftamount > 0 && rightamount > 0)
{
//Fordward
dir = 0;
}

if (leftamount < 0 && rightamount < 0)
{
//Reverse
dir = 1;
}

if (leftamount <= 0 && rightamount > 0)
{
//Left
dir = 2;
}

if (leftamount > 0 && rightamount <= 0)
{
//Right
dir = 3;
}

resetencoders();

switch(dir)
{

case 0:
while (SensorValue[in15] + SensorValue[in16] <= leftamount + rightamount)
{
if (SensorValue[in15] > SensorValue[in16])
{
motor[port1] = 127 - (SensorValue[in15] - SensorValue[in16]);
motor[port2] = 127;
}
if (SensorValue[in16] > SensorValue[in15])
{
motor[port1] = 127;
motor[port2] = 127 - (SensorValue[in16] - SensorValue[in15]);
}
if (SensorValue[in15] == SensorValue[in16])
{
motor[port1] = 127;
motor[port2] = 127;
}
}
break;

case 1:
while (SensorValue[in15] + SensorValue[in16] >= leftamount + rightamount)
{
if (SensorValue[in15] < SensorValue[in16])
{
motor[port1] = -127 - (SensorValue[in15] - SensorValue[in16]);
motor[port2] = -127;
}
if (SensorValue[in16] < SensorValue[in15])
{
motor[port1] = -127;
motor[port2] = -127 - (SensorValue[in16] - SensorValue[in15]);
}
if (SensorValue[in15] == SensorValue[in16])
{
motor[port1] = -127;
motor[port2] = -127;
}
}
break;

case 2:
motor[port1] = -127;
motor[port2] = 127;
while (motor[port1] != 0 || motor[port2] != 0)
{
////////////////////////////Left Motor/////////////////////////////////
if (leftamount - SensorValue[in15] < 0)
{

if (leftamount - SensorValue[in15] <= -50 && leftamount - SensorValue[in15] >= -127)
{
motor[port1] = leftamount - SensorValue[in15];
}

else if (leftamount - SensorValue[in15] < -127)
{
motor[port1] = -127;
}

else if (leftamount - SensorValue[in15] > -50)
{
motor[port1] = -50;
}

}
else
{
motor[port1] = 0;
}

////////////////////////////Right Motor/////////////////////////////////
if (rightamount - SensorValue[in16] > 0)
{

if (rightamount - SensorValue[in16] >= 50 && rightamount - SensorValue[in16] <= 127)
{
motor[port2] = rightamount - SensorValue[in16];
}

else if (rightamount - SensorValue[in16] > 127)
{
motor[port2] = 127;
}

else if (rightamount - SensorValue[in16] < 50)
{
motor[port2] = 50;
}

}
else
{
motor[port2] = 0;
}

}
break;


case 3:
motor[port1] = 127;
motor[port2] = -127;
while (motor[port1] != 0 || motor[port2] != 0)
{
////////////////////////////Right Motor/////////////////////////////////
if (rightamount - SensorValue[in16] < 0)
{

if (rightamount - SensorValue[in16] <= -50 && rightamount - SensorValue[in16] >= -127)
{
motor[port2] = rightamount - SensorValue[in16];
}

else if (rightamount - SensorValue[in16] < -127)
{
motor[port2] = -127;
}

else if (rightamount - SensorValue[in16] > -50)
{
motor[port2] = -50;
}

}
else
{
motor[port2] = 0;
}

////////////////////////////Left Motor/////////////////////////////////
if (leftamount - SensorValue[in15] > 0)
{

if (leftamount - SensorValue[in15] >= 50 && leftamount - SensorValue[in15] <= 127)
{
motor[port1] = leftamount - SensorValue[in15];
}

else if (leftamount - SensorValue[in15] > 127)
{
motor[port1] = 127;
}

else if (leftamount - SensorValue[in15] < 50)
{
motor[port1] = 50;
}

}
else
{
motor[port1] = 0;
}

}
break;



}
}
}
