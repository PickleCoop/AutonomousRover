#include "LCD1602A.h"
#include "delayTimer.h"
#include "string.h"
void initLCD(void) {
    SYSCTL_RCGCGPIO_R |= 0x02; // enable clock to PORTB
    //SYSCTL_RCGCGPIO_R |= 0x01; // enable clock to PORTA
    SYSCTL_RCGCGPIO_R |= 0x10; // enable clock to PORTE
    /* PA7-PA4 output */
    GPIO_PORTB_DIR_R |= 0xF0;
    GPIO_PORTB_DEN_R |= 0xF0;
    /* PE0-PE2 output */
    GPIO_PORTE_DIR_R |= 0x07;
    GPIO_PORTE_DEN_R |= 0x07;
    //GPIO_PORTA_DIR_R |= 0x70;
    //GPIO_PORTA_DEN_R |= 0x70;
    writeCmdLCD(0x20); /* select 5x7 font size and 2 rows of LCD */
    writeCmdLCD(0x28); /* Select 4-bit Mode of LCD */
    writeCmdLCD(0x06); /* shift cursor right */
    writeCmdLCD(0x01); /* clear whatever is written on display */
    writeCmdLCD(0x0F); /* Enable Display and cursor blinking */
    writeCmdLCD(0x01); /* clear whatever is written on display */
    timer1DelayMs(500);
    displayLCD("Initialization", "Complete!");
}
void displayLCD(char *line1, char *line2) {
    writeCmdLCD(0x0F);
    writeCmdLCD(0x80); //First Row
    writeCmdLCD(0x01); //Clear Display
    writeStrLCD(line1);
    //timer1DelayMs(1000);
    writeCmdLCD(0xC0); //Second Row
    writeStrLCD(line2);
    writeCmdLCD(0x0C); //Turn Cursor off.
    timer1DelayMs(500);
}

void writeCmdLCD(unsigned char command) {
    GPIO_PORTB_DATA_R &= ~(0xF0);
    GPIO_PORTB_DATA_R = (command & 0xF0);
    GPIO_PORTE_DATA_R = 0x4; //Enable
    GPIO_PORTE_DATA_R &= ~0x2; //Write
    GPIO_PORTE_DATA_R |= 0x1; //Data reg
    timer1DelayUs(0);
    GPIO_PORTE_DATA_R &= ~0x4;
    GPIO_PORTB_DATA_R = ((command << 4) & 0xF0);
    GPIO_PORTE_DATA_R = 0x4;
    GPIO_PORTE_DATA_R &= ~0x2;
    GPIO_PORTE_DATA_R &= ~0x1; //CMD reg?
    timer1DelayUs(0);
    // GPIO_PORTE_DATA_R &= ~0x4;;
    GPIO_PORTE_DATA_R = 0x00;
    if (command < 4) {
        timer1DelayMs(3); //Increased from 2 ms to 3 ms, fixed text problem.
    } else {
        timer1DelayUs(40);
    }
}

void writeNibbleLCD(unsigned char data) {
    // clear the data pins
    GPIO_PORTB_DATA_R &= ~(0xF0); //Clear bits 4 to 7
    GPIO_PORTB_DATA_R |= (data & 0xF0); //Assign New four bits
    GPIO_PORTE_DATA_R = 0x4;; //Enable Pin
    GPIO_PORTE_DATA_R &= ~0x2;; //Write
    GPIO_PORTE_DATA_R |= 0x1;; //Reg Select: data reg
    timer1DelayUs(0);
    GPIO_PORTE_DATA_R &= ~0x4;; //Disable display.
    GPIO_PORTB_DATA_R = ((data << 4) & 0xF0);
    GPIO_PORTE_DATA_R = 0x4;;
    GPIO_PORTE_DATA_R &= ~0x2;; //Write
    GPIO_PORTE_DATA_R |= 0x1;; //Select data
    timer1DelayUs(0);
    // GPIO_PORTE_DATA_R &= ~0x4;;
    GPIO_PORTE_DATA_R = 0x00;
}

void writeCharLCD(unsigned char data) {
    writeNibbleLCD(data);
    timer1DelayUs(40);
}

void writeStrLCD(char *str) {
    for(int i = 0; str[i] != 0; i++) {
        writeCharLCD(str[i]);
    }
}
