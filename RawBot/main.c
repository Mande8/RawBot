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
//	P06 - Ultrasound Echo Trigger
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
char lcdBuffer[1][16] = { 0 };
unsigned long usRawTimerValue = 0;
unsigned int usDistance = 0;
unsigned int lcdUpdate = 0;

int start = 0;
int stop = 0;
int isrclear = 0;

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
	digitalWrite(0, 4, 0); // Stop the trigger signal
	Timer8UsTrig_Stop();
}

#pragma interrupt_handler Timer16UsEcho_ISR
void Timer16UsEcho_ISR(void) {
	start = 9999;
}

#pragma interrupt_handler GPIO_ISR
void GPIO_ISR(void) {
	//digitalWrite(1,0,1);
	if (US_ECHO_Data_ADDR & US_ECHO_MASK) {
		Timer16UsEcho_WritePeriod(46400);
		Timer16UsEcho_Start(); // Used to measure time until echo signal is returned 
		start++;
	} else {
		usRawTimerValue = Timer16UsEcho_wReadTimer();
		Timer16UsEcho_Stop();
		ltoa(lcdBuffer[0], usRawTimerValue, 10);
		stop++;
	}
	
	gpioTick = true;
	isrclear = PRT1DR;
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
	// backlight(1);

	while(1) {
		if(gpioTick) {
			gpioTick = false;
		}
		
		if(timer8MainTick) {
			timer8MainTick = false;
			lcdUpdate++;
			
			if (lcdUpdate >= 499) {
				lcdUpdate = 0;		
				LCD_Control(0x01);
				LCD_PrString(lcdBuffer[0]);
				
				usDistance = (((46400-usRawTimerValue)/2) / 58);
				itoa(lcdBuffer[1], usDistance,10);
				
				itoa(lcdBuffer[1], start, 10);
				LCD_Position(0,10);
				LCD_PrString(lcdBuffer[1]);
				
				itoa(lcdBuffer[1], stop, 10);
				LCD_Position(1,10);
				LCD_PrString(lcdBuffer[1]);
				
				itoa(lcdBuffer[1], usDistance, 10);
				LCD_Position(1,0);
				LCD_PrString(lcdBuffer[1]);
			}
			
			if(timer8MainCount >= 99) {
				timer8MainCount = 0;
				usTrigSend();
			}
		}
	}
}