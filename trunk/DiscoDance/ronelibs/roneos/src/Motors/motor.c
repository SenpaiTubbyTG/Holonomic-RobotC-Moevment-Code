/**
 * @file motor.c
 */

#ifdef PART_LM3S9B92
#include "inc/lm3s9b92.h"
#endif
#ifdef PART_LM3S8962
#include "inc/lm3s8962.h"
#endif

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_qei.h"

#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/qei.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"

#include "roneos.h"


/******** Defines ********/

#ifdef PART_LM3S9B92
/**MOT0 only includes the mapping for the F port**/
#define PWM0 			GPIO_PA6_PWM0
#define PWM1 			GPIO_PA7_PWM1
#define PWM0_PORT_BASE 	GPIO_PORTA_BASE
#define PWM1_PORT_BASE 	GPIO_PORTA_BASE
#define PWM0_PERIPH 	SYSCTL_PERIPH_GPIOA
#define PWM1_PERIPH 	SYSCTL_PERIPH_GPIOA
#define PWM0_PIN 		GPIO_PIN_6
#define PWM1_PIN 		GPIO_PIN_7

/**MOT1**/
#define PWM2 			GPIO_PH0_PWM2
#define PWM3 			GPIO_PH1_PWM3
#define PWM2_PORT_BASE 	GPIO_PORTH_BASE
#define PWM3_PORT_BASE 	GPIO_PORTH_BASE
#define PWM2_PERIPH 	SYSCTL_PERIPH_GPIOH
#define PWM3_PERIPH 	SYSCTL_PERIPH_GPIOH
#define PWM2_PIN 		GPIO_PIN_0
#define PWM3_PIN 		GPIO_PIN_1

#endif

#ifdef PART_LM3S8962
/**MOT0**/
#define PWM0 			GPIO_PF0_PWM0
#define PWM1 			GPIO_PG1_PWM1
#define PWM0_PORT_BASE 	GPIO_PORTF_BASE
#define PWM1_PORT_BASE 	GPIO_PORTG_BASE
#define PWM0_PERIPH 	SYSCTL_PERIPH_GPIOF
#define PWM1_PERIPH 	SYSCTL_PERIPH_GPIOG
#define PWM0_PIN 		GPIO_PIN_0
#define PWM1_PIN 		GPIO_PIN_1

/**MOT1**/
#define PWM2 			GPIO_PB0_PWM2
#define PWM3 			GPIO_PB1_PWM3
#define PWM2_PORT_BASE 	GPIO_PORTB_BASE
#define PWM3_PORT_BASE 	GPIO_PORTB_BASE
#define PWM2_PERIPH 	SYSCTL_PERIPH_GPIOB
#define PWM3_PERIPH 	SYSCTL_PERIPH_GPIOB
#define PWM2_PIN 		GPIO_PIN_0
#define PWM3_PIN 		GPIO_PIN_1

#endif

#define MOTOR_PWM_FREQUENCY 	22000
#define MOTOR_COMMAND_TIMEOUT 	20

#define MOTOR_FORWARD 		0
#define MOTOR_REVERSE 		1

#define VELOCITY_MAX 		300

#define MOTOR_KFF 			22
#define MOTOR_KFF_OFFSET 	36
#define MOTOR_KP 			80
#define MOTOR_KD 			15
#define MOTOR_KI   			40



/******** structs ********/

typedef struct motorVelocityData {
	uint8 motor;
	uint32 time;
	uint32 ticks;
	int32 vel;
	int32 velGoal;
	int32 error;
	int32 iTerm;
} motorVelocityData;



/******** functions ********/
void motorVelocityDataInit(motorVelocityData* velPtr, uint8 motor);


/******** variables ********/
uint32 motor_command_timer;
motorVelocityData motorData[MOTORS_NUM];



/**
 * 	@brief Enables PWM according to the specified motor.
 *
 * 	@param motor specifies left or right motor (MOTOR_RIGHT/MOTOR_LEFT)
 * 	@returns void
 */
void motor_enable_pwm(int16 motor) {
	unsigned long ulPeriod;
	volatile uint32 ulLoop;  // make this volatile so it doesn't get optimized away

	uint32 port_base_a = 0;
	uint32 port_base_b = 0;
	uint32 port_periph_a = 0;
	uint32 port_periph_b = 0;
	uint8 pin_a = 0;
	uint8 pin_b = 0;
	uint32 pwm_a = 0;
	uint32 pwm_b = 0;
	uint32 pwmgen = 0;
	uint8 pwmoutbit = 0;

	//mot0 = pa6,pa7, mot1 = ph0,ph1 lm3s9b92
	//mot0 = pf0, pg1, mot1 = pe0, pe1
	if (motor == MOTOR_RIGHT) {
		port_base_a = PWM0_PORT_BASE;
		port_base_b = PWM1_PORT_BASE;
		port_periph_a = PWM0_PERIPH;
		port_periph_b = PWM1_PERIPH;
		pin_a = PWM0_PIN;
		pin_b = PWM1_PIN;
		pwm_a = PWM0;
		pwm_b = PWM1;
		pwmgen = PWM_GEN_0;
		pwmoutbit = PWM_OUT_0_BIT | PWM_OUT_1_BIT;
	} else if (motor == MOTOR_LEFT) {
		port_base_a = PWM2_PORT_BASE;
		port_base_b = PWM3_PORT_BASE;
		port_periph_a = PWM2_PERIPH;
		port_periph_b = PWM3_PERIPH;
		pin_a = PWM2_PIN;
		pin_b = PWM3_PIN;
		pwm_a = PWM2;
		pwm_b = PWM3;
		pwmgen = PWM_GEN_1;
		pwmoutbit = PWM_OUT_2_BIT | PWM_OUT_3_BIT;
	} else {
		return;
	}

	//enable the peripherals
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
	MAP_SysCtlPeripheralEnable(port_periph_a);
	MAP_SysCtlPeripheralEnable(port_periph_b);
	// Wait for port to be enabled.
	for (ulLoop = 0; ulLoop < 10; ) {ulLoop++;}

	//set the pins as pwm pins
	GPIOPinConfigure(pwm_a);
	GPIOPinConfigure(pwm_b);
	MAP_GPIOPinTypePWM(port_base_a, pin_a);
	MAP_GPIOPinTypePWM(port_base_b, pin_b);

	// Compute the PWM period based on the system clock.
	ulPeriod = MAP_SysCtlClockGet() / MOTOR_PWM_FREQUENCY;

	// Set the PWM period.
	MAP_PWMGenConfigure(PWM_BASE, pwmgen, PWM_GEN_MODE_UP_DOWN
			| PWM_GEN_MODE_NO_SYNC);
	MAP_PWMGenPeriodSet(PWM_BASE, pwmgen, ulPeriod);

	// Enable the PWM generator.
	MAP_PWMGenEnable(PWM_BASE, pwmgen);
	//enable output state.
	MAP_PWMOutputState(PWM_BASE, pwmoutbit, true);
}

/**
 * 	@brief Initializes variables of the motorVelocityData struct.
 *
 * 	Initializations include motor, ticks, velGoal, iTerm, and error.
 * 	Sets motor and ticks according to the input parameter.
 * 	Sets the others to zero.
 *	@param velPtr a pointer that points to the motorVelocityData struct
 * 	@param motor specifies which motor you want
 * 	@returns void
 */
void motorVelocityDataInit(motorVelocityData* velPtr, uint8 motor) {
	velPtr->motor = motor;
	velPtr->ticks = encoder_get_ticks(motor);;
	velPtr->velGoal = 0;
	velPtr->iTerm = 0;
	velPtr->error = 0;
}

/**
 * @brief Initializes motor.
 *
 * Enables PWM and initializes the motorVelocityData struct for both left and right motor.
 * Also sets the command timer to 0
 * @returns void
 */
void motor_init() {
	motor_enable_pwm(MOTOR_LEFT);
	motor_enable_pwm(MOTOR_RIGHT);
	motorVelocityDataInit(&motorData[MOTOR_LEFT], MOTOR_LEFT);
	motorVelocityDataInit(&motorData[MOTOR_RIGHT], MOTOR_RIGHT);
	motor_command_timer = 0;
}


/**
 * @brief Sets PWM duty cycle for the specified motor and signal.
 *
 * @param motor left or right motor
 * @param signal forward or backward
 * @param dutyCycle duty cycle of PWM
 * @returns 0 if the properties are successfully set; -1 if any of the input parameter is not recognized
 */
int motor_set_pwm_internal(int motor, int signal, int dutyCycle) {
	unsigned long ulPeriod;

	uint32 pwmouta = 0;
	uint32 pwmoutb = 0;
	ulPeriod = MAP_SysCtlClockGet() / MOTOR_PWM_FREQUENCY;

	if (dutyCycle >= 100) {
		dutyCycle = 100;
		ulPeriod = (ulPeriod * 99) / 100;
	} else if (dutyCycle < 0) {
		dutyCycle = 0;
		ulPeriod = 0;
	} else {
		ulPeriod = (ulPeriod * dutyCycle) / 100;
	}

	if (motor == MOTOR_LEFT) {
		pwmouta = PWM_OUT_0;
		pwmoutb = PWM_OUT_1;
	} else if (motor == MOTOR_RIGHT) {
		pwmouta = PWM_OUT_2;
		pwmoutb = PWM_OUT_3;
	} else {
		return -1;
	}

	if (signal == MOTOR_FORWARD) {
		MAP_PWMPulseWidthSet(PWM_BASE, pwmouta, ulPeriod);
	} else if (signal == MOTOR_REVERSE) {
		MAP_PWMPulseWidthSet(PWM_BASE, pwmoutb, ulPeriod);
	} else {
		return -1;
	}
	return 0;
}

/**
 * @brief Resets motor timer.
 *
 * Resets the motor timer to 20 and disables the charger.
 * @returns void
 */
void motor_command_timer_reset(void) {
	motor_command_timer = MOTOR_COMMAND_TIMEOUT;
	charger_disable();
}

/**
 * @brief Sets PWM duty cycle for the specified motor.
 *
 * Sets PWM duty cycle for the specified motor for both reverse and forward signals.
 * @param motor left or right motor
 * @param dutyCycle duty cycle of PWM
 * @returns void
 */
void motor_set_pwm(uint32 motor, int32 dutyCycle) {
	int motReverseLine = 0;
	int motForwardLine = 0;

	if (motor == MOTOR_LEFT) {
		motReverseLine = MOTOR_REVERSE;
		motForwardLine = MOTOR_FORWARD;
	} else if (motor == MOTOR_RIGHT) {
		motReverseLine = MOTOR_REVERSE;
		motForwardLine = MOTOR_FORWARD;
	} else {
		return;
	}

	if (dutyCycle == 0) {
		// stop (coast)
		motor_set_pwm_internal(motor, motReverseLine, 0);
		motor_set_pwm_internal(motor, motForwardLine, 0);
	} else if (dutyCycle > 0) {
		motor_command_timer_reset();
		// forward
		motor_set_pwm_internal(motor, motReverseLine, dutyCycle);
		motor_set_pwm_internal(motor, motForwardLine, 0);
	}
	if (dutyCycle < 0) {
		motor_command_timer_reset();
		//reverse
		motor_set_pwm_internal(motor, motReverseLine, 0);
		motor_set_pwm_internal(motor, motForwardLine, -dutyCycle);
	}
}

/**
 * @brief Converts velocity to pwm
 *
 * @param goalvelocity velocity to be converted
 * @returns converted pwm
 */
int32 vel_to_pwm(int32 goalvelocity){
	int32 pwm;

	if (goalvelocity > 0){
		pwm = (goalvelocity * MOTOR_KFF) / 100 + MOTOR_KFF_OFFSET;
	} else if (goalvelocity < 0){
		pwm = (goalvelocity * MOTOR_KFF) / 100 - MOTOR_KFF_OFFSET;
	} else {
		pwm = 0;
	}
	return pwm;
}

/**
 * @brief Updates the velocity data for one motor.
 *
 * @param velPtr pointer to motorVelocityData
 * @returns void
 */
void motor_velocity_update_one(motorVelocityData* velPtr){
	uint32 ticks = encoder_get_ticks(velPtr->motor);
	uint32 curtime = osTaskGetTickCount();
	uint32 dtime = curtime - velPtr->time;
	int32 vel, dticks;
	int32 ffterm, pterm, dterm, iterm;
	int32 PWM, error, derror;

//	static uint32 printTimer = 0;
//    if (velPtr->motor == MOTOR_LEFT){
//    	printTimer++;
//    }

	if (dtime == 0) {
		return;
	}

	dticks = encoder_delta_ticks(ticks, velPtr->ticks);
	vel = (dticks * 625) / ((int32)dtime * 10);
//    if ((velPtr->motor == MOTOR_LEFT) && ((printTimer % 4) == 0)) {
////    	serial_send_long(" new=",curticks);
////    	serial_send_long(" old=",velPtr->ticks);
//    	serial_send_long(" dt=",encoder_delta_ticks(curticks, velPtr->ticks));
//    	serial_send_long(" v=",vel);
//    	serial_send_long(" vg=",motorData[velPtr->motor].velGoal);
//
//    }

    error    = velPtr->velGoal - vel;
    derror   = error - velPtr->error;
    ffterm   = (vel_to_pwm(velPtr->velGoal));
    pterm    = MOTOR_KP * error;
    dterm    = -MOTOR_KD * derror;
    iterm    = velPtr->iTerm + MOTOR_KI * error;
    //			8 bits  (16bits  16bits  16bits)/8bits  = 18bits in numer
    PWM      = ffterm + (pterm + dterm + iterm)/100;

    velPtr->vel = vel;
    velPtr->time = curtime;
    velPtr->ticks = ticks;

//    if ((velPtr->motor == MOTOR_LEFT) && ((printTimer % 4) == 0)) {
//    	serial_send_long(" e=",error);
//    	serial_send_float(" ff=",ffterm);
//    	serial_send_float(" p=",pterm);
//    	serial_send_float(" d=",dterm);
//    	serial_send_float(" i=",iterm);
//		serial_send_long(" PWM=",PWM);
//		serial_send_string_crlf("");
//    }

    if (velPtr->velGoal == 0) {
        iterm = 0.0;
        error = 0.0;
        PWM = 0;
    }
    velPtr->iTerm = iterm;
    velPtr->error = error;

    PWM = bound(PWM, -100, 100);
	motor_set_pwm(velPtr->motor, PWM);
}

/**
 * @brief Updates the velocity data for both motors.
 *
 * @returns void
 */
void motor_velocity_update(void){
	motor_velocity_update_one(&motorData[MOTOR_LEFT]);
	motor_velocity_update_one(&motorData[MOTOR_RIGHT]);
	// compute tv, rv
}

/**
 * @brief Breaks one motor with the specified duty cycle.
 *
 * @param motor (left or right)
 * @param dutyCycle duty cycle of PWM
 */
void motor_brake(uint32 motor, int32 dutyCycle) {
	int motForwardLine = 0;
	int motReverseLine = 0;

	if (motor == MOTOR_LEFT) {
		motForwardLine = MOTOR_FORWARD;
		motReverseLine = MOTOR_REVERSE;
	} else if (motor == MOTOR_RIGHT) {
		motForwardLine = MOTOR_FORWARD;
		motReverseLine = MOTOR_REVERSE;
	} else {
		return;
	}
	motor_command_timer_reset();
	// brake
	motor_set_pwm_internal(motor, motForwardLine, 100);
	motor_set_pwm_internal(motor, motReverseLine, 100);
}

/**
 * @brief Updates the motor command timer.
 *
 * If no motor command has been received, timeout and enables the charger.
 * This function should be called at 10 hz.
 * @returns void
 */
void motor_command_timer_update(void) {
	//
	if (motor_command_timer > 0) {
		motor_command_timer--;
	}

	if (motor_command_timer == 0) {
		// we have not received a motor command in a while.  Timeout and enable the charger
		motor_set_pwm(MOTOR_LEFT, 0);
		motor_set_pwm(MOTOR_RIGHT, 0);

		// enable charger
		charger_enable();
	}
}

/**
 * @brief Sets the current velocity of the specified motor.
 *
 * @param motor left or right motor
 * @param velocity motor velocity to be set
 * @returns void
 */
void motor_set_velocity(uint32 motor, int32 velocity) {
	if ((motor == MOTOR_LEFT) || (motor == MOTOR_RIGHT)) {
		motorData[motor].velGoal = velocity;
	}
}

/**
 * @brief Gets the current velocity of the specified motor.
 *
 * @param motor left or right motor
 * @returns the current velocity; 0 if the input parameter is not recognized
 */
int32 motor_get_velocity(uint32 motor) {
	if ((motor == MOTOR_LEFT) || (motor == MOTOR_RIGHT)) {
		return motorData[motor].vel;
	} else {
		return 0;
	}
}

/**
 * @brief Sets the translational and radial velocity of the motor.
 *
 * @returns void
 */
void motor_set_tv_rv(int32 tv, int32 rv){
	int32  velLeft = boundAbs(tv - rv * MOTOR_WHEEL_BASE / 2000, VELOCITY_MAX);
	int32 velRight = boundAbs(tv + rv * MOTOR_WHEEL_BASE / 2000, VELOCITY_MAX);
	motor_set_velocity(MOTOR_LEFT, velLeft);
	motor_set_velocity(MOTOR_RIGHT, velRight);
}

/**
 * @brief Gets the translational and radial velocity of the motor.
 *
 * @returns void
 */
void motor_get_tv_rv(int32* tvPtr, int32* rvPtr){
	int32 velL = motorData[MOTOR_LEFT].vel;
	int32 velR = motorData[MOTOR_RIGHT].vel;
	*tvPtr = (velL + velR) / 2;
	*rvPtr = (velR - velL) * 1000 / MOTOR_WHEEL_BASE;
}


