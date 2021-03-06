#pragma config(Sensor, in1,    armPot,              sensorPotentiometer)
#pragma config(Sensor, in2,    clawPot,             sensorPotentiometer)
#pragma config(Sensor, in3,    lineFollower,        sensorLineFollower)
#pragma config(Sensor, dgtl1,  rightEnc,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEnc,             sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  sonar,               sensorSONAR_cm)
#pragma config(Motor,  port1,           arm,           tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           right,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           left,          tmotorNormal, openLoop)
#pragma config(Motor,  port6,           right2,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           left2,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           claw,          tmotorNormal, openLoop)
#pragma config(Motor,  port10,          arm2,          tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

void pre_auton()
{
	SensorValue[armPot] = 0;
	SensorValue[clawPot] = 0;
	SensorValue[rightEnc] = 0;
	SensorValue[leftEnc] = 0;
}

//Variables for program to run

//variables for positions of the potentiometers
int goal_high_high = 3289;
int goal_high_low = 2900;
int goal_low_high = 3006;
int goal_low_low = 2470;
int floor_pos = 2220;
int claw_open = 1348;
int claw_closed = 1750;
int cpStart=600;
int arm_top_goal_high = 3289;
int arm_top_goal_low = 2900;
int arm_low_goal = 3006;
int arm_base = 2470;
int arm_floor = 2220;
int low_power = 32;
int mid_power = 64;
int high_power = 127;

//variables dealing with the dimensions of robot.
int robot_width = 17.5;//width of base of robot in cm

/*
MoveRobot moves the robot either forward or backwards.
Ticks is the number of ticks to move the robot forward by. Enter 0 to disable ticks.
Time is how long the robot will run if encoders are disabled. Enter 0 to disable time.
If time and ticks are both disabled, then the robot will run forward at the specified speed without end.
*/
void MoveRobot (int power, int time, int ticks)
{
  if (ticks > 0){
    time1[T2] = 0;
    while(SensorValue[rightEnc] < ticks&& time1[T2]<3*time){

      motor[left] = power;
      motor[left2] = power;
      motor[right] = power;
      motor[right2] = power;
    }
  }
  else if(time > 0){
    time1[T1] = 0;
    while(time1[T1] < time){
      motor[left] = power;
      motor[left2] = power;
      motor[right] = power;
      motor[right2] = power;
    }
  }
  else{
    motor[left] = power;
    motor[left2] = power;
    motor[right] = power;
    motor[right2] = power;
  }
}

/*
MoveArm moves the arm to a certain position that is specified at the power that is specified.
The program doesnt care what position the arm starts at and will move to the specified position.
*/
void MoveArm (int power, int pos){
  do{
    if (SensorValue[armPot] < pos){
      motor[arm] = power;
      motor[arm2] = power;
    }
    else if(SensorValue[armPot] > pos){
      motor[arm] = -power;
      motor[arm2] = -power;
    }
    else{
      motor[arm] = 15;
      motor[arm2] = 15;
    }
  }while(SensorValue[armPot] != pos);
}

/*
MoveClaw opens or closes the claw to match the specified position at the specified power.
*/
void MoveClaw (int power, int pos){
  do{
    if (SensorValue[clawPot] < pos){
      motor[claw] = power;
    }
    else if(SensorValue[clawPot] > pos){
      motor[claw] = -power;
    }
    else{
      motor[claw] = 0;
    }
  }while(SensorValue[clawPot] != pos);
  motor[claw] = 0;
}

/*
PivotTurn turns the robot in place at the specified power.
The disabling of time and ticks works the same way as in the MoveRobot function.
Positive power turns left and negative power turns right. THINK RADIANS!!!
*/
void PivotTurn (int power, int time, int ticks){
  if (ticks > 0){
    while(SensorValue[rightEnc] < ticks){
      motor[left] = -power;
      motor[left2] = -power;
      motor[right] = power;
      motor[right2] = power;
    }
  }
  else if(time > 0){
    time1[T1] = 0;
    while(time1[T1] < time){
      motor[left] = -power;
      motor[left2] = -power;
      motor[right] = power;
      motor[right2] = power;
    }
  }
  else{
    motor[left] = -power;
    motor[left2] = -power;
    motor[right] = power;
    motor[right2] = power;
  }
}

/*
VeerTurn has the robot move forward while veering to one side or the other at a specified speed.
The speed is for the speed of the center of the robot. Radius should be entered in cm.
Positive radius turns left, negative radius turns right.
*/
void VeerTurn (int power, int radius, int ticks, int time){
  int right = 0;
  int left = 0;

  right = (power*(radius + (robot_width/2)))/radius;
  left = (power*(radius - (robot_width/2)))/radius;

  if(ticks > 0){
    while(SensorValue[rightEnc] <= ticks){
      motor[right] = right;
      motor[right2] = right;
      motor[left] = left;
      motor[left2] = left;
    }
  }
  else if(time > 0){
    time1[T1] = 0;
    while(time1[T1] < time){
      motor[right] = right;
      motor[right2] = right;
      motor[left] = left;
      motor[left2] = left;
    }
  }
  else{
    motor[right] = right;
    motor[right2] = right;
    motor[left] = left;
    motor[left2] = left;
  }
}

//Stop is a function to stop all used motors for use in both autonomous and tele-op modes.
void Stop(){
  motor[arm] = 0;
  motor[arm2] = 0;
  motor[claw] = 0;
  motor[right] = 0;
  motor[right2] = 0;
  motor[left] = 0;
  motor[left2] = 0;
}


int armscale(int input)        // for arm
{
  if(input<0)
    return .5*input;
  if(input>=0)
    return 1*input;
  return 0;
}
int clawScale(int limit_switch)        // for claw
{
  int c=SensorValue(clawPot);
  int min_rotation = 800;
  if((c<=cpStart+min_rotation) && (limit_switch > 0))
    return 0;
 else
    return -63;
}
int scale(int input)          // for drive train
{
  if(input<=96&&input>=-96)     //if between -96 and 96, run half power
    return .5*input;
  if(input<-96)                 // if less than -96, run at (80/32)-48 power ---> full power
    return 80/32*input-48;
  if(input>96)
    return 79/31*input+48;      // if greater than 96, run at (79/32)+48 power ---> full power
  return 0;
}
int scale2(int input)          // for drive train scale v2
{
  int da=32;// declare input changes
  int db=64;
  int dc=127;
  int ma=.2;// declare multipliers
  int mb=.35;
  int mc=(dc-(ma*da+db*mb))/(dc-db);
  if(input<=da&&input>=-da)     //if between -1st benchmark and 1st benchmark, run lowest multiplier
    return ma*input;
  if(input>=-db&&input<-da)                 // -1st>input>=-2nd, run at (.7)-32 power
    return mb*input-da*ma;
  if(input<=db&&input>da)                 // 64<input<=96, run at (.7)+32 power
    return mb*input+da*ma;
  if(input<-db)                 // if less than -96, run at (29/32)-99 power ---> ful/////l power
    return mc*input-da*ma-db*mb;
  if(input>db)                  // if greater than 96, run at (28/31)+99 power ---> full power
    return mc*input+da*ma+db*mb;
  return 0;
}
void move(int left_power,int right_power,int wait_time)		//Function definition for move
{
	motor[left] = left_power;		   //Motor on left is set to power level specified in left_power parameter
  motor[left2] = left_power;
	motor[right] = right_power;			//Motor on right is set to power level specified in right_power parameter
  motor[right2] = right_power;
	if (wait_time > 0) wait1Msec(wait_time);	//Waits the number of milliseconds specified in the wait_time parameter
}
void DriveTimeSmall(int drive_time, int drive_power, int counts)
{

  float slow_factor = 0.9;
  int start_enc, end_enc;
  int check_counts=0;
  if(counts>0) check_counts = 1;
  SensorValue(rightEnc)=0;
  SensorValue(leftEnc)=0;
  ClearTimer(T1);
  end_enc = SensorValue(rightEnc);
  while ((check_counts && (abs(end_enc) < counts)) || (!check_counts &&time1[T1] < drive_time)) {

    if (SensorValue(leftEnc) == SensorValue(rightEnc)) {
      move(drive_power, drive_power, 0);
    } else if (SensorValue(leftEnc) > SensorValue(rightEnc)) {
      move ((int)drive_power*slow_factor,drive_power,0);
    } else {
      move (drive_power, (int)drive_power*slow_factor,0);
    }
    end_enc = SensorValue(rightEnc);
  }

}
void DriveTime(int drive_time, int drive_power, int counts)
{
  int block_size = 100;
  if (counts > block_size) {
    int batch_count = counts/block_size;
    for (int i = 0; i < batch_count; i++) {
      int counts_left = counts - i*block_size;
      int small_count = counts_left;
      if (small_count > block_size) small_count = block_size;
      DriveTimeSmall(drive_time, drive_power, counts);
    }
  } else {
    DriveTimeSmall(drive_time, drive_power, counts);
  }
  move(0,0,0);
}

task autonomous()
{
	MoveRobot(-110,200,1.0);// robot moves back hopefully dropping the preload
	wait1Msec(1500);
	MoveRobot(110,400, 2.0);- //moves forward
	MoveClaw(100,claw_closed);//closes over preload
  MoveRobot(-110,900, 3.0);//move back
	MoveArm(111,goal_high_high);//move arm up
  MoveRobot(110,900, 4.0);// go over goal?
  MoveArm(111,goal_high_low);
  MoveArm(60,goal_high_low+60);
  MoveClaw(100,claw_open);



}
task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
	  /*right- port 2,6
	  left- port 3,7
	  claw- port 8
	  arm- port 1,10*/

    motor[port2] = scale2(vexRT[Ch3] - vexRT[Ch4]);        // arcade drive
    motor[port6] = scale2(vexRT[Ch3] - vexRT[Ch4]);
    motor[port3] = scale2(vexRT[Ch3] + vexRT[Ch4]);
    motor[port7] = scale2(vexRT[Ch3] + vexRT[Ch4]);

    //Arm left joystick ch3
    motor[port1]=armscale(vexRT[Ch2]);
    motor[port10]=armscale(vexRT[Ch2]);
    int limit_pressed = (vexRT[Btn6D] != 0);
    //Claw open (port 8)ch6
    if (vexRT[Btn6U] != 0 ||vexRT[Btn5U] != 0 )
      motor[port8]= 127;
    if (vexRT[Btn6D] != 0||vexRT[Btn5D] != 0 )
      motor[port8] = clawScale(limit_pressed);
    else if( vexRT[Btn6U] == 0&&vexRT[Btn5U] == 0 )
      motor[port8] = 0;
    if (vexRT[Btn7U] != 0 && time1[T2] > 1000) {
       DriveTime(500, 32, 120);
       ClearTimer(T2);
    }
    if (vexRT[Btn7D] != 0 && time1[T2] > 1000) {
      DriveTime(500, -32, 120);
      ClearTimer(T2);
    }
    //
    // Update Lights
    //
	}
}
