#include "hc05.h"
#include "delayTimer.h"
#include "string.h"

void initHC05(void) {
	GPIO_PORTE_AMSEL_R = 0x00; // Disable analog function
	GPIO_PORTE_PCTL_R = 0x00110000; // GPIO clear bit PCTL
	GPIO_PORTE_DEN_R = 0x30; // Enable digital pins PE3-PE0
	GPIO_PORTE_AFSEL_R = 0x30; // Alternate function
	
	SYSCTL_RCGCUART_R |= 0x20;
	timer1DelayMs(500);
	UART5_CTL_R = 0;
	UART5_IBRD_R = 325;
	UART5_FBRD_R = 34;
	UART5_CC_R = 0;
	UART5_LCRH_R = 0x60;
	UART5_CTL_R = 0x301;
}

int recievedDataHC05() {
	return ((UART5_FR_R & (1<<4)) == 0);
}

char readHC05(void) {
	char data;
	while((UART5_FR_R & (1<<4)) != 0); 
	//switchCheck();
	data = UART5_DR_R ; /* before giving it another byte */
	return (unsigned char) data;
}

void writeHC05(unsigned char data) {
	while ((UART5_FR_R & 0x20)!=0);
	UART5_DR_R = data;
}

void writeStrHC05(char *str) {
	int i;
	for (i=0; i < strlen(str); i++){
		writeHC05(str[i]);
	}
}
