#define gyro_accumulation_period 10 //heading will update based on gyro reading once every [this value] milliseconds
int heading = 0;//starting heading is zero bearing, this variable will always store the robot's current heading relative to its starting heading
ClearTimer(T1);//clears T1 timer, which will be used to scale the gyro reading
while(true) {
  if(time1[T1] > gyro_accumulation_period) {
    heading += (int) ((float) SensorValue[gyro] * (float) time1[T1]);//float typecasting needed to maintain precision
    ClearTimer(T1);
  }
  
}
