                                                                           What is a gyro?
The gyro (short for gyroscope) does not measure angle or direction per se (that would be a compass).  Instead, it measures rate of rotational change, so measurements taken by the gyroscope are in the 
units of degrees/second.

How is it useful?
Degrees per second is not degrees, but what does a gyro measure? Rate of change, or derivative as math snobs like to say.  Therefore, to obtain degrees from degrees per second, we need to 
integrate with respect to 
time.  

from Programming Update 1, integration is accomplished through use of an accumulator variable inside the infinite loop that constantly adds the gyro degrees/second value weighted by a time value.  
Sample code might look something like this:




#define gyro_accumulation_period 10 //heading will update based on gyro reading once every [this value] milliseconds
int heading = 0;//starting heading is zero bearing, this variable will always store the robot's current heading relative to its starting heading
ClearTimer(T1);//clears T1 timer, which will be used to scale the gyro reading
while(true) {
  if(time1[T1] > gyro_accumulation_period) {
    heading += (int) ((float) SensorValue[gyro] * (float) time1[T1]);//float typecasting needed to maintain precision
    ClearTimer(T1);
  }
  
}