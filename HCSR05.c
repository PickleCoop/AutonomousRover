 #include "HCSR05.h"
#include "delayTimer.h"

void initHCSR05() {
    SYSCTL_RCGC2_R |= 0x00000002; // Port B clock initialized
  GPIO_PORTB_DIR_R |= (1U << 1);
  GPIO_PORTB_DEN_R |= (1U << 1); // PB1 digital enable
	
	SYSCTL_RCGCTIMER_R |= (1U << 2); // activate timer2
  SYSCTL_RCGCGPIO_R |= (1U << 1);  /* enable clock to PORTB */
  while ((SYSCTL_PRGPIO_R & 0x0002) == 0); // ready?
  GPIO_PORTB_DIR_R &= ~(1U << 0);  /* make PB0 an input pin */
  GPIO_PORTB_DEN_R |= (1U << 0);   /* make PB0 as digital pin */
  GPIO_PORTB_AFSEL_R |= (1U << 0); /* use PB0 alternate function */
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF0F) + 0x00000007;
	

  TIMER2_CTL_R &= ~1;                                 /* disable timer2A during setup */
  TIMER2_CFG_R = 0x04;                                /* Timer2A in 16-bit timer mode */
  TIMER2_TAMR_R = 0x17;                               /* Timer2A enable up-count and capture mode */
                                                      /* capture rising and falling edges on PB0 pin */
  TIMER2_CTL_R |= 0x0C; /* capture the rising edge */ // (1<< 2) | (1 << 3);
  TIMER2_CTL_R |= 0x1;                                /* enable Timer2A */
}

float getSonarDistance() {
	triggerSonar();
	int regValue = captureSonarEcho();
	return convertDistance(regValue);
}

void triggerSonar() {
	GPIO_PORTB_DATA_R &= ~(1U << 1); // Clear trigger
  timer1DelayUs(10);
  GPIO_PORTB_DATA_R |= (1U << 1); // Set trigger
  timer1DelayUs(10);
  GPIO_PORTB_DATA_R &= ~(1U << 1); // Clear trigger
}

float convertDistance(int timePeriod) {
	timer1DelayMs(10);
  float distance = ((float) timePeriod) * 20 / 10000000;
  distance = (343.0 * distance) / 2.0;
	timer1DelayMs(10);
  return distance;
}

int captureSonarEcho() {
	int risingEdge, fallingEdge;
  while (1)
  {
    TIMER2_ICR_R = 4; /* clear timer0A capture flag */
    while ((TIMER2_RIS_R & (1 << 2)) == 0)
      ;                           /* wait till captured */
    if (GPIO_PORTB_DATA_R & (1U << 0)) /*check if rising edge occurs */
    {
      risingEdge = TIMER2_TAR_R; /* save the timestamp */
      TIMER2_ICR_R = 4;          /* clear timer0A capture flag */
      /* detect falling edge */
      while ((TIMER2_RIS_R & (1 << 2)) == 0)
        ;                         /* wait till captured */
      fallingEdge = TIMER2_TAR_R; /* save the timestamp */
			TIMER2_ICR_R = 4;
      return (fallingEdge - risingEdge) &
             0x00FFFFFF; /* return the time difference */
    }
  }
}