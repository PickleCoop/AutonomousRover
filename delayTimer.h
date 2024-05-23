//TIMER1 is used as delay timer.
#define SYSCTL_RCGCTIMER_R (*((volatile unsigned long *)0x400FE604))
#define TIMER1_CFG_R (*((volatile unsigned long *)0x40031000))
#define TIMER1_TAMR_R (*((volatile unsigned long *)0x40031004))
#define TIMER1_CTL_R (*((volatile unsigned long *)0x4003100C))
#define TIMER1_IMR_R (*((volatile unsigned long *)0x40031018))
#define TIMER1_RIS_R (*((volatile unsigned long *)0x4003101C))
#define TIMER1_MIS_R (*((volatile unsigned long *)0x40031020))
#define TIMER1_ICR_R (*((volatile unsigned long *)0x40031024))
#define TIMER1_TAILR_R (*((volatile unsigned long *)0x40031028))
#define TIMER1_TAPR_R (*((volatile unsigned long *)0x40031038))

/**
 * Helper method, initializes Timer 1 for delays.
 * All delay functions uses this helper.
 *
 * @param select16 selects 16-bit or 32-bit timer, 16-bit = 1, 32-bit = 0.
 * @param perscalar is the value to set on prescalar
 */
void timer1Init(unsigned int select16, unsigned int prescalar);

/**
 * Runs a delay in seconds.
 * 
 * @param ttime is how many seconds our delay will be.
 */
void timer1Delay(int ttime);

/**
 * Runs a delay in milliseconds.
 * 
 * @param ttime is how many milliseconds our delay will be.
 */
void timer1DelayMs(int ttime);

/**
 * Runs a delay in microseconds.
 * 
 * @param ttime is how many microseconds our delay will be.
 */
void timer1DelayUs(int ttime);
