#pragma config(Sensor, dgtl1,  encL,                sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encR,                sensorQuadEncoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
const float gearRatio = 3.2;
int distance()
{
  return (abs(SensorValue[encL]) + abs(SensorValue[encR])/2 * gearRatio/360*PI);
}

void fowards(float ticks)
{
  while(distance() < ticks)
  {
    motor[port1] = 127;
    motor[port2] = 127;
  }
  motor[port1] = 0;
  motor[port2] = 0;
}

task main()
{
  fowards(5);
}