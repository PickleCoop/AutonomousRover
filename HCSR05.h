//Sonar Device PB0 = echo, PB1 = trigger.

//Port B:
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_AFSEL_R 			(*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGCGPIO_R 			(*((volatile unsigned long *)0x400FE608))
#define SYSCTL_PRGPIO_R 				(*((volatile unsigned long *)0x400FEA08))

//Timer 2 to monitor echo.
#define TIMER2_CFG_R (*((volatile unsigned long *)0x40032000))
#define TIMER2_TAMR_R (*((volatile unsigned long *)0x40032004))
#define TIMER2_TBMR_R (*((volatile unsigned long *)0x40032008))
#define TIMER2_CTL_R (*((volatile unsigned long *)0x4003200C))
#define TIMER2_SYNC_R (*((volatile unsigned long *)0x40032010))
#define TIMER2_IMR_R (*((volatile unsigned long *)0x40032018))
#define TIMER2_RIS_R (*((volatile unsigned long *)0x4003201C))
#define TIMER2_MIS_R (*((volatile unsigned long *)0x40032020))
#define TIMER2_ICR_R (*((volatile unsigned long *)0x40032024))
#define TIMER2_TAILR_R (*((volatile unsigned long *)0x40032028))
#define TIMER2_TBILR_R (*((volatile unsigned long *)0x4003202C))
#define TIMER2_TAMATCHR_R (*((volatile unsigned long *)0x40032030))
#define TIMER2_TBMATCHR_R (*((volatile unsigned long *)0x40032034))
#define TIMER2_TAPR_R (*((volatile unsigned long *)0x40032038))
#define TIMER2_TBPR_R (*((volatile unsigned long *)0x4003203C))
#define TIMER2_TAPMR_R (*((volatile unsigned long *)0x40032040))
#define TIMER2_TBPMR_R (*((volatile unsigned long *)0x40032044))
#define TIMER2_TAR_R (*((volatile unsigned long *)0x40032048))
#define TIMER2_TBR_R (*((volatile unsigned long *)0x4003204C))
#define TIMER2_TAV_R (*((volatile unsigned long *)0x40032050))
#define TIMER2_TBV_R (*((volatile unsigned long *)0x40032054))
#define TIMER2_RTCPD_R (*((volatile unsigned long *)0x40032058))
#define TIMER2_TAPS_R (*((volatile unsigned long *)0x4003205C))
#define TIMER2_TBPS_R (*((volatile unsigned long *)0x40032060))
#define TIMER2_TAPV_R (*((volatile unsigned long *)0x40032064))
#define TIMER2_TBPV_R (*((volatile unsigned long *)0x40032068))
#define TIMER2_PP_R (*((volatile unsigned long *)0x40032FC0))

void initHCSR05(void);
float getSonarDistance(void);
void triggerSonar(void);
float convertDistance(int timePeriod);
int captureSonarEcho(void);
