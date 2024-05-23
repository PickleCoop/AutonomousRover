#include <stdint.h>
// #include <tm4c123gh6pm.h>
#include "motorDriver.h"
#include "delayTimer.h"

#define SYSCTL_RCGCPWM_R (*((volatile unsigned long *)0x400FE640))
#define SYSCTL_RCGCGPIO_R (*((volatile unsigned long *)0x400FE608))
#define GPIO_PORTA_AFSEL_R (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DEN_R (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_PCTL_R (*((volatile unsigned long *)0x4000452C))
#define GPIO_PORTA_DIR_R (*((volatile unsigned long *)0x40004400))

#define PWM1_2_CTL_R (*((volatile unsigned long *)0x400290C0))
#define PWM1_2_GENB_R (*((volatile unsigned long *)0x400290E4))
#define PWM1_2_LOAD_R (*((volatile unsigned long *)0x400290D0))
#define PWM1_2_CMPB_R (*((volatile unsigned long *)0x400290DC))
#define PWM1_ENABLE_R (*((volatile unsigned long *)0x40029008))
#define PWM1_2_CMPA_R (*((volatile unsigned long *)0x400290D8))
#define PWM1_2_GENA_R (*((volatile unsigned long *)0x400290E0))
#define GPIO_PORTA_DATA_R (*((volatile unsigned long *)0x400043FC))
#define SYSCTL_RCC_R (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_PRGPIO_R (*((volatile unsigned long *)0x400FEA08))
#define GPIO_PORTA_AMSEL_R (*((volatile unsigned long *)0x40004528))

#define GPIO_PORTF_AFSEL_R (*((volatile unsigned long *)0x40025420))

#define GPIO_PORTF_PCTL_R (*((volatile unsigned long *)0x4002552C))
#define GPIO_PORTF_AMSEL_R (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_DEN_R (*((volatile unsigned long *)0x4002551C))

#define PWM1_3_CTL_R (*((volatile unsigned long *)0x40029100))
#define PWM1_3_GENA_R (*((volatile unsigned long *)0x40029120))
#define PWM1_3_LOAD_R (*((volatile unsigned long *)0x40029110))
#define PWM1_3_CMPA_R (*((volatile unsigned long *)0x40029118))
/**
 * PA7
 * PA2 = in4
 * PA3 = in3
 * PA5 = in2
 * PA6 = 1
 * PA7 used to generate PWM, not connected.
 **/
// // Function to initialize PWM for motor speed control
// void initPWM(void)
// {
//     // Enable PWM1 module clock
//     SYSCTL_RCGCPWM_R |= 0x02; // 0x02;
//     SYSCTL_RCC_R &= ~0x00100000; // Use PWM divider

//     // Enable GPIO port that contains the PWM pins
//     SYSCTL_RCGCGPIO_R |= 0x01;

//     // Configure PWM pins for motor 1 (PA6) and motor 2 (PA7)
//     GPIO_PORTA_AFSEL_R |= 0x80;        // Enable alternate function PA7
//     GPIO_PORTA_PCTL_R |= (0x05 << 28); // Configure PA7
//     GPIO_PORTA_DEN_R |= 0x80;          // Enable digital functionality on PA7

//     PWM1_2_CTL_R &= ~(1<<0);
//     // PWM1_2_CTL_R &= ~(1<<1);  
//     // Configure PWM module for motor 2 (PWM1B)
//     // PWM1_2_CTL_R = 0;          // Disable PWM during configuration
//     PWM1_2_GENB_R = 0x80C;      // Drive PWM1B high when the counter matches CMPB and low when the counter matches LOAD
//     PWM1_2_LOAD_R = 50000 - 1; // Set PWM period (50,000 cycles for 1 kHz PWM frequency)
//     PWM1_2_CMPB_R = 0;         // Initialize PWM1B duty cycle (0% initially)
//     PWM1_2_CTL_R |= 0x01;      // Enable PWM

//     // Enable PWM output for motor 2 (PWM1B)
//     PWM1_ENABLE_R |= 0x20; // Enable PWM1B output
// } 

// Function to initialize PWM for motor speed control
void initPWM(void)
{
	 int volatile delay;
    // Enable M1PWM6 on PF2
    SYSCTL_RCGCPWM_R |= 0x02;  // 1) activate PWM1
    SYSCTL_RCGCGPIO_R |= 0x20; // 2) activate port F
    while ((SYSCTL_PRGPIO_R & 0x20) == 0)
    {
    };
		delay = SYSCTL_PRGPIO_R;    
    SYSCTL_RCC_R |= 0x000E0000;
    GPIO_PORTF_AFSEL_R |= (1 << 2);   // enable alt funct on PF2
    GPIO_PORTF_PCTL_R &= ~0x00000F00; // configure PF2 as M1PWM6
    GPIO_PORTF_PCTL_R |= 0x00000500;
    GPIO_PORTF_AMSEL_R &= ~0x04;  // disable analog functionality on PF2
    GPIO_PORTF_DEN_R |= (1 << 2); // enable digital I/O on PF2

    PWM1_3_CTL_R &= ~(1 << 0); // 3) disable PWM1
    PWM1_3_CTL_R &= ~(1 << 1); // 4) re-loading down-counting mode
    PWM1_3_GENA_R = 0x0000008C;

    PWM1_3_LOAD_R = 5000;        // 5) cycles needed to count down to 0
    PWM1_3_CMPA_R = 4999;        // 6) count value when output rises
    PWM1_3_CTL_R |= 0x00000001;  // 7) start PWM1
    PWM1_ENABLE_R |= 0x00000040; // enable PF2/M1PWM6
}

// Function to set motor speeds
void setMotorSpeed(int speedMotor1, int speedMotor2)
{
    // Calculate duty cycles based on speeds
    int dutyCycleMotor1 = (speedMotor1 * MAX_DUTY_CYCLE) / 100;
    int dutyCycleMotor2 = (speedMotor2 * MAX_DUTY_CYCLE) / 100;

    // Set PWM duty cycles for motors
    PWM1_2_CMPA_R = dutyCycleMotor1 * (PWM1_2_LOAD_R + 1) / 100; // Set duty cycle for motor 1 (PWM1A)
   // PWM1_2_CMPB_R = dutyCycleMotor2 * (PWM1_2_LOAD_R + 1) / 100; // Set duty cycle for motor 2 (PWM1B)
    PWM1_2_GENA_R = 0x8C;                                        // Drive PWM1A high when the counter matches CMPA and low when the counter matches LOAD
    GPIO_PORTF_AFSEL_R |= (1<<2);                                  // Enable alternate function PF2
    GPIO_PORTF_PCTL_R |= 0x00000500;                           // Configure PA6
    GPIO_PORTF_DEN_R |= (1 << 2);                                   // Enable digital functionality on PF2
}

void turn(int pin, int delay)
{
    GPIO_PORTA_DIR_R |= pin;
    GPIO_PORTA_DEN_R |= pin;
    GPIO_PORTA_DATA_R |= pin;
    timer1DelayUs(delay); // example 500000
    GPIO_PORTA_DATA_R &= ~pin;
}

void run(int pin1, int pin2)
{
    GPIO_PORTA_DIR_R |= (pin1 | pin2);
    GPIO_PORTA_DEN_R |= (pin1 | pin2);
    GPIO_PORTA_DATA_R |= (pin1 | pin2);

    timer1DelayUs(500000);

    GPIO_PORTA_DATA_R &= ~(pin1 | pin2);
}

void initMotorDriver(void)
{
    initPWM();
  //  setMotorSpeed(0, 0);
}

void brake(void)
{
    setMotorSpeed(0, 0);
}

void turn45Left(void)
{
    setMotorSpeed(NO_SPEED, TURN_ANGLE_SPEED);
    timer1DelayUs(50000);
    setMotorSpeed(NO_SPEED, NO_SPEED);
    timer1DelayUs(5);
    run(DEFAULT_SPEED, DEFAULT_SPEED);
}

void turn45Right(void)
{
    setMotorSpeed(TURN_ANGLE_SPEED, NO_SPEED);
    timer1DelayUs(50000);
    setMotorSpeed(NO_SPEED, NO_SPEED);
    timer1DelayUs(5);
    run(DEFAULT_SPEED, DEFAULT_SPEED);
}

void turn90(void)
{
    setMotorSpeed(TURN_ANGLE_SPEED, 0);
    timer1DelayUs(100000);
    setMotorSpeed(0, 0);
    timer1DelayUs(5);
    run(DEFAULT_SPEED, DEFAULT_SPEED);
}

void turn135(void)
{
    setMotorSpeed(TURN_ANGLE_SPEED, 0);
    timer1DelayUs(200000);
    setMotorSpeed(0, 0);
    timer1DelayUs(5);
    run(DEFAULT_SPEED, DEFAULT_SPEED);
}
void turnLeft(int angle)
{
    switch (angle)
    {
    case 45:
        turn45Left();
        break;
    case 90:
        turn90();
        break;
    case 135:
        turn135();
        break;
    default:
        break;
    }
}
void turnRight(int angle)
{
    switch (angle)
    {
    case 45:
        turn45Right();
        break;
    default:
        break;
    }
}
