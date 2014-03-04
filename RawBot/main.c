/**********
*  Notes  *
**********/

// Connections:
// Port 0 - Outputs
//	P00 - HBRIDGE_IN1
//	P01 - HBRIDGE_IN2
//	P02 - HBRIDGE_IN3
//	P03 - HBRIDGE_IN4
//	P04 - 
//	P05 - 
//	P06 - US_TRIG
//	P07 - SERVO
// Port 1 - Inputs
//	P10 - Not usable
//	P11 - 
//	P12 - 
//	P13 - 
//	P14 - 
//	P15 - 
//	P16 - 
//	P17 - US_ECHO

/*************
*  Includes  *
*************/

#include <m8c.h>
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
unsigned long usDistance = 0;
int isrClear = 0;
int usEchoRisingEdge = 0;
int usEchoFallingEdge = 0;
unsigned int servoMiddle = 300;
unsigned int servoRange = 200;
int servoAngle = 0;

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
void Timer16UsEcho_ISR(void) {
	int timer16Overflow = 1;
	timer16Overflow++;
}

#pragma interrupt_handler GPIO_ISR
void GPIO_ISR(void) {
	gpioTick = true;
	
	// Echo signal rising edge
	if (US_ECHO_Data_ADDR & US_ECHO_MASK) {
		Timer16UsEcho_WritePeriod(46400);	
		Timer16UsEcho_Start(); // Used to measure time until echo signal is returned
		usEchoRisingEdge++;
		
	// Echo signal falling edge
	} else {
		usRawTime = Timer16UsEcho_wReadTimer();
		lcdAssign(usRawTime, LCD_TOP);
		usDistance = usCalculateDistance(usRawTime);
		lcdAssign(usDistance, LCD_BOTTOM);
		Timer16UsEcho_Stop();
		usEchoFallingEdge++;
	}
	
	isrClear = PRT1DR; // Needed for ChangeFromRead interrupt type
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
	servoStart(3999);

	while (1) {
		if (timer8MainTick) {
			timer8MainTick = false;
			
			if (timer8MainTick % 3) {
				drive(HALT); // Slowing down the motors
			} else {
				
			}
			
			if (timer8MainCount % 9) {
				lcdPrint();
			}
			
			// Every 1,0s
			if (timer8MainCount >= 999) {
				timer8MainCount = 0;
				usTrigSend();
			}
		}
	}
}