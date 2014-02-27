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

/************************
* Function declarations *
*************************/

void setup(void);
void usTrigSend(void);
void drive(BYTE);
void digitalWrite(BYTE, BYTE, BYTE);
void pinMode(BYTE, BYTE, BYTE);

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
	if (US_ECHO_Data_ADDR & US_ECHO_MASK)
	{
		Timer16UsEcho_WritePeriod(46400);
		Timer16UsEcho_Start(); // Used to measure time until echo signal is returned 
		start++;
	}
	else
	{
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
	setup();

	while(1) {
		if(gpioTick) {
			gpioTick = false;
		}
		
		if(timer8MainTick) {
			timer8MainTick = false;
			lcdUpdate++;
			
			if (lcdUpdate >= 499)
			{
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

/**************
*  Functions  *
**************/

void setup(void) {
	int moi = 0;
	M8C_EnableGInt;
	M8C_EnableIntMask(INT_MSK0, INT_MSK0_GPIO);
	LCD_Init();
	LCD_Start();
	Timer8UsTrig_EnableInt();
	Timer8UsTrig_Start();
	Timer8Main_EnableInt();
	Timer8Main_Start();
	
	Timer16UsEcho_EnableInt();
	backlight(1);
	for (moi = 0; moi < 9999; moi++);
}

// Sends ultrasound trigger signal
void usTrigSend(void) {
	digitalWrite(0, 4, 1); // Start the trigger signal
	Timer8UsTrig_Start(); // Used to measure 10us trigger pulse
}

// Used to drive the H-Bridge; think of a numpad for controls
// 5 = 00 00 = 8 = stop
// 8 = 10 10 = xx = forward (L&R forward)
// 2 = 01 01 = xx = backward  (L&R backwards)
// 4 = 01 10 = xx = left    (L back   R forward)
// 6 = 10 01 = xx = right (L forward  R backwards)
// 7 = 00 10 = xx = left move(L coast R forward)
// 9 = 10 00 = xx = right mov(L forward L coast)
void drive(BYTE dir) {
	switch (dir){
		case 5: // Stop
		PRT0DR &= ~0xFF; // All pins low
		break;
	case 8: // Forward (1010)
		PRT0DR &= ~0x5;
		PRT0DR |= 0xA;
		break;
	case 2: // Back (0101)
		PRT0DR &= ~0xA;
		PRT0DR |= 0x5;
		break;
	case 4: // Left (01 10)
		PRT0DR &= ~0x9;
		PRT0DR |= 0x6;
		break;
	default:
		PRT0DR &= ~0x15; // All pins low
		break;
	} 
}

// Sets the pin mode
void pinMode(BYTE port, BYTE pin, BYTE state) {
	int i;
	BYTE bitMask = 1;
	for(i = 0; i < pin; i++) { bitMask *= 2; }

	switch (state){
		case 0: // Resistive Pulldown
			if(port == 0) { PRT0DM2 &= ~bitMask; PRT0DM1 &= ~bitMask; PRT0DM0 &= ~bitMask; }
			else if(port == 1) { PRT1DM2 &= ~bitMask; PRT1DM1 &= ~bitMask; PRT1DM0 &= ~bitMask; }
			else if(port == 2) { PRT2DM2 &= ~bitMask; PRT2DM1 &= ~bitMask; PRT2DM0 &= ~bitMask; }
			break;
		case 1: // Strong
			if(port == 0) { PRT0DM2 &= ~bitMask; PRT0DM1 &= ~bitMask; PRT0DM0 |= bitMask; }
			else if(port == 1) { PRT1DM2 &= ~bitMask; PRT1DM1 &= ~bitMask; PRT1DM0 |= bitMask; }
			else if(port == 2) { PRT2DM2 &= ~bitMask; PRT2DM1 &= ~bitMask; PRT2DM0 |= bitMask; }
			break;
		case 3: // Pull up
			if(port == 0) { PRT0DM2 &= ~bitMask; PRT0DM1 |= bitMask; PRT0DM0 |= bitMask; }
			else if(port == 1) { PRT1DM2 &= ~bitMask; PRT1DM1 |= bitMask; PRT1DM0 |= bitMask; }
			else if(port == 2) { PRT2DM2 &= ~bitMask; PRT2DM1 |= bitMask; PRT2DM0 |= bitMask; }
			break;
		default:
			break;
	} 
}

// Function for setting pins
// 0 = low, 1 = high, 2 = toggle
void digitalWrite(BYTE port, BYTE pin, BYTE state) {
	int i ;
	BYTE bitMask = 1; 
	for(i = 0; i < pin; i++) { bitMask *= 2; }

	switch (state){
		case 0:
			if(port == 0) PRT0DR &= ~bitMask;
			else if(port == 1) PRT1DR &= ~bitMask;
			else if(port == 2) PRT2DR &= ~bitMask;
			break;
		case 1:
			if(port == 0) PRT0DR |= bitMask;
			else if(port == 1) PRT1DR |= bitMask;
			else if(port == 2) PRT2DR |= bitMask;
			break;    
		case 2:
			if(port == 0) PRT0DR ^= bitMask;
			else if(port == 1) PRT1DR ^= bitMask;
			else if(port == 2) PRT2DR ^= bitMask;
			break;
		default:
			break;
	}
}

void backlight(BYTE toggle)
{
	pinMode(2,7,1); // set the pin to strong
	if (toggle == 0) { BL_Data_ADDR=(BL_DataShadow&=~BL_MASK); }
	else if (toggle == 1) { BL_Data_ADDR=(BL_DataShadow|=BL_MASK); }
	else if (toggle == 2) { BL_Data_ADDR=(BL_DataShadow^=BL_MASK); }
}