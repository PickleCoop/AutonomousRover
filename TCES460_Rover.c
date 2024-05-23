//Include basic headers.
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>

#include "PLL.h"
//Include all headers for each module.
#include "delayTimer.h"
#include "HC05.h"
#include "HCSR05.h"
#include "motorDriver.h"
#include "LCD1602A.h"

float distance = 0;

int speed = 10;

#define PA2 0x04 // left  wheel in1 forward
#define PA6 0x40 // right wheel in4 forward
#define PA3 0x08 // left  wheel in2 backward
#define PA5 0x20 // right wheel in3 backward

void EnableInterrupts(void);
void initPortEInterrupts(void);

int main(){
	PLL_Init();
    char bluetoothInput;
    char bluetoothBuffer[50];
    int on = 0; //Boolean to turn on and off.
		char lcdBuffer[20]; //Buffer containing text to print on LCD second row.
		sprintf(lcdBuffer, "Distance: 0.0 cm");
	
    initHC05();
    initHCSR05();
		initMotorDriver();
    EnableInterrupts();
		float distance2 = 0;

		initLCD();
		timer1DelayMs(100);
		displayLCD("Steven Tieu", lcdBuffer);
		int count = 0;

    while(1){
        if(on == 0) {
            bluetoothInput = readHC05(); //Waits for interrupt.
            if(bluetoothInput == 'N') {
                on = 1;
                writeStrHC05("Rover Activated\n");

            }
            timer1DelayMs(500);
        } else { //on == 1
            distance = getSonarDistance();
						distance2 = distance; //distance eraseed after sprintf();
            sprintf(bluetoothBuffer, "Sonar Distance: %f cm\n", distance);
            writeStrHC05(bluetoothBuffer);
						sprintf(lcdBuffer, "Dist.: %0.2f cm", distance2);
						displayLCD("Team7", lcdBuffer);
            if(distance <= 1000 && count < 2){
                //turn right 45 degrees
                turnRight(45);
                count++;
            } else if(distance <= 1000 && count == 2){
                //turn left 135 degrees.
                turnLeft(135);
                count++;
            } else if(distance <= 1000 && count == 3){
                //turn left 45 degrees.
                turnLeft(45);
                count++;
            } else if(distance <= 1000 && count == 4){
                //turn 90 degrees (180 degrees from original.)
                turnRight(180);
            } else {
                count = 0;
                //go forward
                //run(speed, speed); // now we need pins instead of integer speed
                run(PA2, PA6); // run forward
            }
            int ifRecieved = recievedDataHC05();
            if (ifRecieved) {
                bluetoothInput = readHC05();
                if(bluetoothInput == 'F') {
                    on = 0;
                }
            }
        }
    }


}











void EnableInterrupts(void)
{
    __asm  ("    CPSIE  I\n");
}