/**********
*  Notes  *
**********/

// Connections:
// Port 0 - Outputs
//	P00 - Hbridge IN1
//	P01 - Hbridge IN2
//	P02 - Hbridge IN3
//	P03 - Hbrdige IN4
//	P04 -
//	P05 - 
//	P06 - Ultrasound Trigger
//	P07 - Servo (ServoPWM connected here)

/*************
*  Includes  *
*************/

#include <m8c.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PSoCAPI.h"
#include "LCD.h"
#include "Timer8Main.h"
#include "Timer8UsTrig.h"
#include "Timer16UsEcho.h"
#include "Functions.h"

/**************************
*  Variable declarations  *
**************************/

bool timer8MainTick = false;
unsigned int timer8MainCount = 0;
bool gpioTick = false;
unsigned long usRawTime = 0;
unsigned int usDistance = 0;
unsigned int lcdUpdate = 0;
int isrClear = 0;

/***********************
*  Interrupt handlers  *
***********************/

#pragma interrupt_handler Timer8Main_ISR
void Timer8Main_ISR(void) {
	timer8MainTick = true;
	timer8MainCount++;
}

#pragma interrupt_handler Timer8UsTrig_ISR
void Timer8UsTrig_ISR(void) {
	digitalWrite(0, 6, 0); // Stop the trigger signal
	Timer8UsTrig_Stop();
}

// usDistance > 400 cm --> no objects in sight
#pragma interrupt_handler Timer16UsEcho_ISR
void Timer16UsEcho_ISR(void) { }

#pragma interrupt_handler GPIO_ISR
void GPIO_ISR(void) {	
	if (US_ECHO_Data_ADDR & US_ECHO_MASK) { // Rising edge
		Timer16UsEcho_Start(); // Used to measure time until echo signal is returned
	} else { // Falling edge
		usDistance = usCalculateDistance(Timer16UsEcho_wReadTimer());
		lcdAssign(usDistance, 0);
		
		Timer16UsEcho_Stop();
	}
	
	gpioTick = true;
	isrClear = PRT1DR;
}

/******************
*  Main function  *
******************/

void main(void) {
	M8C_EnableGInt;
	M8C_EnableIntMask(INT_MSK0, INT_MSK0_GPIO);
	LCD_Init();
	LCD_Start();
	Timer8UsTrig_EnableInt();
	Timer8UsTrig_Start();
	Timer8Main_EnableInt();
	Timer8Main_Start();
	Timer16UsEcho_EnableInt();

	while (1) {		
		if (gpioTick) {
			gpioTick = false;
		}
		
		if (timer8MainTick) {
			timer8MainTick = false;
			lcdUpdate++;
			
			if (lcdUpdate >= 499) {
				lcdUpdate = 0;
				
				lcdAssign(usCalculateDistance(34422), 3);
				
				lcdPrint();
			}
			
			// 1 s
			if (timer8MainCount >= 99) {
				timer8MainCount = 0;
				usTrigSend();
			}
		}
	}
}