tasks main()
{
	cleargyro();
	while (SensorValue[gyro] < 500)
 	{
		turn_right();

	}
	stopallmotors();
	(Sensorvalue[gyro] = 1000);
	while(SensorValue[gyro] > 500)
	{
	  turn_left();
	}

	stopallmotors();
}
