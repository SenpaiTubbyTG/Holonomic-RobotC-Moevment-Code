//Pre-Auton goes here
void pre_auton()
{

//Encoders:
  SensorValue[EncoderL] = 0;
  SensorValue[EncoderR] = 0;

//Arm:
  arm_grounded = SensorValue[PotArm];    // sets ground point
  low_descore_point = arm_grounded + 500; // sets low descore arm pooint
  low_lock_point = arm_grounded + 800;   //...lowgoal
  high_lock_point = arm_grounded + 1100; // ...high goal
  arm_grounded += 250;
}
