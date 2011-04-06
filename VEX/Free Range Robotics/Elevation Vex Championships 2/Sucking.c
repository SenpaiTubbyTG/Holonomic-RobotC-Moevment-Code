void startsucking()
{
motor[port7] = -127;
motor[port8] = -127;
}

void stopsucker()
{
motor[port7] = 0;
motor[port8] = 0;
}

void startejecting()
{
motor[port7] = 127;
motor[port8] = 127;
}

void ejectblocks(int amount)
{
SensorValue[in13] = 0;
SensorValue[in14] = 0;
motor[port7] = 90;
motor[port8] = 90;
while (SensorValue[in13] + SensorValue[in14] <= amount)
{
}
motor[port7] = 0;
motor[port8] = 0;
}
