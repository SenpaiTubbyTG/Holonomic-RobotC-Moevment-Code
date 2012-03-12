#include"Functions"
task main ()
{
int current_pos = SensorValue[gyro];
int final = current_pos + 500;
while([SensorValue[gyro] < final])
  {
	turn_right();

  }
stopallmotors();
}