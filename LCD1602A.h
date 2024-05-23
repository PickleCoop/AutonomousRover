//PORT C
#define GPIO_PORTB_DATA_R (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_PUR_R (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_CR_R (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R (*((volatile unsigned long *)0x4000552C))
#define SYSCTL_RCGC2_R (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGCGPIO_R (*((volatile unsigned long *)0x400FE608))
/// Create definition for PORT A registers
/*
#define GPIO_PORTA_DATA_R (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_PUR_R (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_CR_R (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R (*((volatile unsigned long *)0x4000452C))
#define SYSCTL_RCGC2_R (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGCGPIO_R (*((volatile unsigned long *)0x400FE608))
*/
// Create definitions for Port E registers
#define GPIO_PORTE_DATA_R (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_PUR_R (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_CR_R (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_AFSEL_R (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PCTL_R (*((volatile unsigned long *)0x4002452C))
/*define useful symbolic names for LCD commands
#define CLR 0x01
#define MOVE_HOME 0x02
#define MOVE_RIGHT 0x06
#define MOVE_LEFT 0x08
#define SHIFT_RIGHT 0x1C
#define SHIFT_LEFT 0x18
#define cursorBlink 0x0F
#define cursorOff 0x0C
#define cursorOn 0x0E
#define Function_set_4bit 0x28
#define Function_set_8bit 0x38
#define Entry_mode 0x06
#define Function_8_bit 0x32
#define FirstRow 0x80
#define SecondRow 0xC0*/

/**PINOUT
 D7 to PB7
 D6 to PB6
 D5 to PB5
 D4 to PB4
 EN to PE2
 RW to PE1
 RS to PE0
*/

void initLCD(void);

/**
* Writes a CMD command to the LCD.
*/
void writeCmdLCD(unsigned char command);
/**
* Prints two input strings on on the two rows of the LCD
* @param line1 is the string to appear on top row.
* @param line2 is the string to appear on the bottom row.
*/
void displayLCD(char *line1, char *line2);
/**
*
*/
void writeNibbleLCD(unsigned char data);
/**
* Writes a character to the LCD data register
* @param data is the character to write.
*/
void writeCharLCD(unsigned char data);
/**
* Writes a string to the LCD data register
* @param str is the string to write.
*/
void writeStrLCD(char *str);