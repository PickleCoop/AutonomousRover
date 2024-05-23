# AutonomousRover
This project is from my embedded systems class, and was the combination of many projects from that quarter. The rover utilizes sonar range detection, bluetooth, PWM modulation for the motors, and an LCD screen. The rover is turned on via bluetooth signal, and will move forward based on the code for the motors. Once an object is detected within a meter, the rover will execute a series of turns to attempt to avoid the obstacle.

# Function Names
HC05: Bluetooth Device Driver  
HCSR05: Sonar Device Driver  
LCD1602A: LCD Screen Driver  
delayTimer: Delay used in other Driver Code  
motorDriver: Driver used for Motors  
tm4c123gh6pm: Header File for Microcontroller  
TCES460_Rover: Main File using the Drivers  

# Authors
Evan Cooper  
Steven Tieu  
Souleymane Dembele  
Jotkamal Jaswal
