#ifndef __H_MOTOR_DRIVER
#define __H_MOTOR_DRIVER
#include "delayTimer.h"

#define PWM_FREQUENCY 1000 // PWM frequency in Hz
#define MAX_DUTY_CYCLE 100 // Maximum duty cycle value (0-100%)
#define DEFAULT_SPEED 25
#define NO_SPEED 0
#define TURN_ANGLE_SPEED 20
/**
 * init the pwm module.
 * @param
 * @return
 */
void initPWM(void);
/**
 * initialize the motor by calling the pwm init.
 * @param
 * @return
 */
void initMotorDriver(void);
/**
 * init the pwm
 * @param speedMotor1, speedMotor2
 * @return
 */
void setMotorSpeed(int speedMotor1, int speedMotor2);

/**
 * move the robot forward.
 * @param pin1, pin2
 * @return
 */
void run(int pin1, int pin2);

/**
 * turn the robot with the given speed.
 * @param pin, delay
 * @return
 */
void turn(int pin, int delay);
/**
 * currently setting the speed of the motors to zero.
 * @param
 * @return
 */
void brake(void);
/**
 * turn left 45 degree.
 * @param
 * @return
 */
void turn45Left(void);
/**
 * turn right 45 degree.
 * @param
 * @return
 */
void turn45Right(void);
/**
 * turn left 90 degree.
 * @param
 * @return
 */
void turn90(void);
/**
 * turn left 135 degree.
 * @param
 * @return
 */
void turn135(void);
/**
 * turn left angle.
 * @param
 * @return
 */
void turnLeft(int angle);
/**
 * turn right angle.
 * @param
 * @return
 */
void turnRight(int angle);

#endif
