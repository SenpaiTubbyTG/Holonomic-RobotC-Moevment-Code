#pragma config(Sensor, in1,    PotArm,              sensorPotentiometer)
#pragma config(Motor,  port1,           ArmLL,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           DriveLF,     tmotorNormal, openLoop)
#pragma config(Motor,  port3,           DriveLB,      tmotorNormal, openLoop)
#pragma config(Motor,  port4,           DriveRF,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           DriveRB,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           ArmLU,      tmotorNormal, openLoop)
#pragma config(Motor,  port7,           ArmRU,     tmotorNormal, openLoop)
#pragma config(Motor,  port8,           collector1,    tmotorNormal, openLoop)
#pragma config(Motor,  port9,           collector2,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          ArmRL,     tmotorNormal, openLoop, reversed)

#define FULL 127
//NOTE 10 IS AN ARBITRARY VALUE, HAS NOT BEEN TESTED
int DeadZone = 10; //dead zone value for joysticks

/*****GENERIC FUNCTIONS********************************************************/

//checks dead zone and scales values excluding deadzone back to 0-127
int checkDeadZone(int x) {
    if (abs(x) < DeadZone) {
        return 0;
    } else {
        if (x < 0)
            return (x + DeadZone)*(FULL / (FULL - DeadZone)
        else
            return (x - DeadZone)*(FULL / (FULL - DeadZone)
        }
}

int getSign(int x) {
    if (x < 0)
        return -1;
    else
        return 1;
    }

//scales input based on function, arcsin by default
int scaleInput(int input) {
    if (input != 0) {
        //Squaring input scaling (technically cubic, used to preserve sign)
        //  leftDrivePower = (left^3)/(127^2);
        return asin(input / 127) / asin(1)*127;
    } else {
        return = 0;
    }
}

//Tube Detection
bool tube_detection() {
    if (SensorValue[DetectTube] < 3075) {
        return true
    } else {
        return false;
    }
}

/*****SET FUNCTIONS************************************************************/

//Set Arm Speed
void setArmSpeed(int speed) {
    motor[ArmLL] = motor[ArmLU] = motor[ArmRL] = motor[ArmRU] = speed;
}

//Set collector speed
void setCollectorSpeed(int speed) {
    motor[SuckR] = motor[SuckL] = speed;
}

//Set Drive Speed (Left & Right)
void setDriveSpeed(int speed) {
    motor[DriveRF] = motor[DriveRB] = motor[DriveLF] = motor[DriveLB] = speed;
}

//Set Right drive speed
void setDriveRSpeed(int speed) {
    motor[DriveRF] = motor[DriveRB] = speed;
}

//Set Left drive speed
void setDriveLSpeed(int speed) {
    motor[DriveLF] = motor[DriveLB] = speed;
}

//Stops drivetrain
void stopDrive() {
    setDriveSpeed(0);
}

//Stop collector
void stopCollector() {
    setCollectorSpeed(0);
}

/*****ARM FUNCTIONS************************************************************/

//Arm Lock
int lock(int final_pos) //locks arm to final_pos potentiometer point
{
    int current_pos = SensorValue(PotArm); //reads potentiometer
            int direction; //up or down?
            int arm_diff = abs(current_pos - final_pos); //difference between current and desired points

    if (arm_diff > 100) { //potentiometer is very precise, so
        if (current_pos > final_pos) {//arm too high
            direction = 1; //will move down
        } else if (current_pos < final_pos) { //arm too low
            direction = -1; //will move up
        }
        setArmSpeed(FULL * direction);
        return 0;
    } else { //in hindsight, I don't think this is necessary
        setArmSpeed(0);
        return 1;
    }
}

/*ARM TIME FUNCTION*/

void lock_msec(int speed, int duration) {

    setArmSpeed(speed);
    wait1Msec(duration);
    setArmSpeed(0);
}

/*SUCKER TIME FUNCTION */

int sucker(int speed, int duration) { //positive numbers for out
    setSuckSpeed(speed);
    wait1Msec(duration);
    setSuckSpeed(0);
    return 1;
}

/* DRIVE FUNCTIONS
 *
 * drive_forward_1msec
 * drive_straight
 * drive_straight_to_touch
 */

int leftDrivePower, rightDrivePower; //drivetrain variables
/* driveTank
* @purpose: Teleop tank drive
* @param leftInput: raw left joystick input, -127 to 127; negative values reverse
* @param rightInput: raw right joystick input, -127 to 127; negative values reverse
* @param scale: boolean value to enable joystick input scaling
* @param filter: boolean value to enable rate filtering
*/

void driveTank(int leftInput, int rightInput, bool scale, bool filter) {
    //checks for dead zone and rescales from -127 to 127
    leftInput = checkDeadZone(leftInput);
    rightInput = checkDeadZone(leftInput);
            //scales initial input by specified function (arcsin)
    if (scale) {
        scaleInput(leftInput);
        scaleInput(rightInput);
    }
    //sets power of drive train based on rate filter
    if (filter) {
        leftDrivePower = rateFilter(leftInput, 1);
                rightDrivePower = rateFilter(rightInput, rightDrivePower, 1);
    } else {
        leftDrivePower = leftInput;
        rightDrivePower = rightInput;
    }
    //sets motors to power values
    setDriveLSpeed(leftDrivePower);
    setDriveRSpeed(rightDrivePower);
}
/* rateFilter
 * @purpose: protect motors from sudden acceleration (teleop)
 * @param JoystickValue: raw joystick input, -127 to 127; negative values reverse
 * @param MotorValue: current motor value, -127 to 127; negative values reverse
 * @param accelRateLimit: maximum limit for acceleration
 */
int rateFilter(int JoystickValue, int MotorValue, int accelRateLimit) {
    if (JoystickValue > 0) { //Want to go fwd
        if (MotorValue >= 0) { //current motor value already going fwd
            if (JoystickValue > MotorValue) {
                MotorValue += accelRateLimit; //accelerating from fwd to faster fwd
            } else {
                MotorValue = JoystickValue; //Declarating to a value greater than zero
            }
        } else { //want to go foward but going rev
            if (MotorValue < -64) {
                MotorValue = MotorValue / 2; //slow down a little
            } else {
                MotorValue = 0; //slow down to zero for a cyle if motor is already going less than half speed
            }
        }
    } else if (JoystickValue < 0) { //Want to go rev
        if (MotorValue <= 0) { //already going rev
            if (JoystickValue > MotorValue) {
                MotorValue -= accelRateLimit; //accelerating from rev to faster rev
            } else {
                MotorValue = JoystickValue; //Declarating to a value less than zero
            }
        } else { //want to go rev but going fwd
            if (MotorValue > 64) {
                MotorValue = MotorValue / 2; //slow down a little
            } else {
                MotorValue = 0; //slow down to zero for a cyle if motor is going slowly
            }
        }
    } else { //should only be when joystick equals 0
        MotorValue = 0;
    }
    return MotorValue;
}

/* drive_forward_msec
 * @purpose: autonomously drive robot forward for provided duration
 * @param speed: speed of motors, -127 to 127; negative values go reverse
 * @param duration: duration in milliseconds
 */
void drive_msec(int speed, int duration) {
    setDriveSpeed(speed);
    wait1Msec(duration);
    killdrive;
}

/* drive_straight
 * @purpose: autonomously drive robot forward for provided distance in inches
 * precondition: 4 inch wheels used; if other wheels, change the 4 in the while loop
 * @param speed: speed of motors, -127 to 127; negative values go reverse
 * @param distance: distance in inches
 * TODO: consider adding an acceleration loop
 *///there are 360 ticks in an encoder revolution

/*void drive(int speed, float distance) {
    SensorValue[EncoderL] = 0;
            SensorValue[EncoderR] = 0;
    while (((float) abs(SensorValue[EncoderL]) * 4 / 360 * PI) < distance &&
            ((float) abs(SensorValue[EncoderR]) * 4 / 360 * PI) < distance) {
        if (abs(SensorValue[EncoderL]) > abs(SensorValue[EncoderR])) {
            setDriveRSpeed(speed);
                    setDriveLSpeed(speed + 1);
        } else if (abs(SensorValue[EncoderL]) < abs(SensorValue[EncoderR])) {
            setDriveRSpeed(speed + 1);
                    setDriveLSpeed(speed);
        } else {

            setDriveSpeed(speed);
        }
    }
    killdrive
}

 drive_straight_unlocked
 * @purpose: autonomously drive robot forward for provided distance in inches WHILE allowing
 * precondition: 4 inch wheels used; if other wheels, change the 4 in the while loop
 * @param speed: speed of motors, -127 to 127; negative values go reverse
 * @param distance: distance in inches
 * TODO: consider adding an acceleration loop
 //there are 360 ticks in an encoder revolution

int drive_unlocked(int speed, float distance) {
    SensorValue[EncoderL] = 0;
            SensorValue[EncoderR] = 0;
    if (((float) abs(SensorValue[EncoderL]) * 2 / 360 * PI) < distance &&
            ((float) abs(SensorValue[EncoderR]) * 2 / 360 * PI) < distance) {
        if (abs(SensorValue[EncoderL]) > abs(SensorValue[EncoderR])) {
            setDriveRSpeed(speed);
                    setDriveLSpeed(speed + 1);
        } else if (abs(SensorValue[EncoderL]) < abs(SensorValue[EncoderR])) {
            setDriveRSpeed(speed + 1);
                    setDriveLSpeed(speed);
        } else {
            setDriveSpeed(speed);
        }
        return 0;
    }

      else
        return 1;
    }

 turn (SAFE)
 * timed, no Sensor
 * in this funtion you set the speed of the left and right sides of the drive train individually
 *@param speedL: speed of left motors
 *@param speedR: speed of right motors
 
void turn_timed(int speedr, int speedl, duration) {
    //right drive

    setDriveRSpeed(speedl);
            //left drive
            setDriveLSpeed(speedr);
            wait1Msec(duration);
            killdrive;
}

 turn
 * @purpose: autonomously execute a point turn
 * @param speed: speed of motors, 0 to 127; no negative values
 * @param degrees: number of degrees to turn, positive degrees go to left
 * TODO: complete this function
 
void turn(int speed, int degrees) {
    SensorValue[EncoderL] = 0;
            SensorValue[EncoderR] = 0;
    while (SensorValue[EncoderL] < degrees || SensorValue[EncoderR] < degrees * 2) {
        setDriveRSpeed(speed);
                setDriveLSpeed(-speed);
    }
    stopDrive();
}*/
