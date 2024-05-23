#include "delayTimer.h"

void repeatTimer(int ttime);

void timer1Init(unsigned int select16, unsigned int prescalar) {
	SYSCTL_RCGCTIMER_R |= 0x02; /* enable clock to Timer1 */
	TIMER1_CTL_R = 0x00; /* disable Timer before initialization */
	TIMER1_CFG_R = (select16 << 2); /* 16-bit option */
	TIMER1_TAMR_R = 0x02; /* periodic mode and down-counter */
	TIMER1_TAILR_R = prescalar - 1; /* Timer A interval load value register */
	TIMER1_ICR_R = 0x1; /* clear the TimerA timeout flag*/
	TIMER1_TAPR_R = 1; // Prescalar value.. Can extend the cycle time max 256 times
	TIMER1_CTL_R |= 0x01; /* enable Timer A after initialization */
}

void timer1Delay(int ttime) {
	timer1Init(0, 16 * 1000 * 1000);
	repeatTimer(ttime);
}

void timer1DelayMs(int ttime) {
	timer1Init(1, 16 * 1000);
	repeatTimer(ttime);
}

void timer1DelayUs(int ttime) {
	timer1Init(1, 16);
	repeatTimer(ttime);
}

void repeatTimer(int ttime) {
	for(int i = 0; i < ttime; i++) {
		while ((TIMER1_RIS_R & 0x01) == 0); /* wait for TimerA timeout flag */
		TIMER1_ICR_R = 0x01; /* clear the TimerA timeout flag */
	}
}
