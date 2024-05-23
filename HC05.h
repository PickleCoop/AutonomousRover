//Using Port E:
#define GPIO_PORTE_DATA_R (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_PUR_R (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_CR_R (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_AFSEL_R (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PCTL_R (*((volatile unsigned long *)0x4002452C))
#define SYSCTL_RCGC2_R (*((volatile unsigned long *)0x400FE108))
	
//Using UART module 5
#define UART5_DR_R (*((volatile unsigned long *)0x40011000))
#define UART5_FR_R (*((volatile unsigned long *)0x40011018))
#define UART5_IBRD_R (*((volatile unsigned long *)0x40011024))
#define UART5_FBRD_R (*((volatile unsigned long *)0x40011028))
#define UART5_LCRH_R (*((volatile unsigned long *)0x4001102C))
#define UART5_CTL_R (*((volatile unsigned long *)0x40011030))
#define UART5_CC_R (*((volatile unsigned long *)0x40011FC8))
#define SYSCTL_RCGCUART_R (*((volatile unsigned long *)0x400FE618))

/** PINOUT
	PE4 to Hc05 Tx
	PE5 to Hc05 Rx
*/

/**
 * Initializes the bluetooth module
 */
void initHC05(void);

/**
 * Checks if the bluetooth module has recieved data
 * @return boolean value, true if data is ready in RX buffer.
 */
int recievedDataHC05(void);

/**
 * Waits for data to appear and reads it.
 */
char readHC05(void);

/**
 * Transmits a byte of data on the bluetooth module.
 */
void writeHC05(unsigned char data);

/**
 * Transmits a string of data on the bluetooth module.
 */
void writeStrHC05(char *str);
