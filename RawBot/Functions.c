/*************
*  Includes  *
*************/

#include "Functions.h"
#include <m8c.h>
#include <stdbool.h>
#include "PSoCAPI.h"

char lcdBuffer[4][8] = { 0 };
int driveDirection = 0;
int driveCounter = 0;

// Returns:
//  true 	= currently moving
//  false 	= not moving
bool driveCounterCheck(void) {
	if (driveCounter == 0) {
		drive(HALT);
		return false;
	} else {
		driveCounter--;
		return true;
	}
}

bool driveAssign(int direction, int counter) {
	drive(HALT); // Clear current drive assigns (not sure about this)
	driveDirection = direction;
	drive(direction);
	driveCounter = counter;
}

/**********
*  Servo  *
**********/

void servoStart(unsigned int period) {
	ServoPWM_WritePeriod(period);
	ServoPWM_Start();	
}

void servoStop(void) {
	ServoPWM_Stop(); // Just for uniformity
}

// Servo moving
void servoMove(int angle, unsigned int middle, unsigned int range) {
	ServoPWM_WritePulseWidth(middle + (angle*((range*2)/180)));
}

/***************
*  Ultrasound  *
***************/

void usTrigSend(void) {
	digitalWrite(0, 6, 1); // Start the trigger signal
	Timer8UsTrig_Start(); // Used to measure 10us trigger pulse
}

unsigned long usCalculateDistance(unsigned long usRawTime) {
	return (((46400 - usRawTime) / 2) / 58);
}

/************
*  Driving  *
************/

// Connections : H-bridge is connected to
// Used to drive the H-Bridge; think of a numpad for controls
// IN1 = Port0 Pin0 , IN2 = Port0 Pin1 etc
void drive(unsigned char dir) {
	switch (dir) {
		case 2: // Back (0101)
			PRT0DR &= ~0x0A;
			PRT0DR |= 0x05;
			break;
		case 4: // Left (0110)
			PRT0DR &= ~0x09;
			PRT0DR |= 0x06;
			break;
		case 5: // Stop
			PRT0DR &= ~0x0F; // All pins low;
			break;
		case 6: // Right (1001)
			PRT0DR &= ~0x06;
			PRT0DR |= 0x09;
			break;
		case 8: // Forward (1010)
			PRT0DR &= ~0x05;
			PRT0DR |= 0x0A;
			break;
		default:
			PRT0DR &= ~0x0F; // All pins low;
			break;
	}	
}

/*****************
*  General PSoC  *
*****************/

// Check positions from Functions.h
void lcdAssign(long lcdNumbers, unsigned int lcdPosition) {
	ltoa(lcdBuffer[lcdPosition], lcdNumbers, 10);
}

void lcdPrint(void) {
	LCD_Control(0x01);

	LCD_Position(0, 0);
	LCD_PrString(lcdBuffer[0]);
	LCD_Position(0, 8);
	LCD_PrString(lcdBuffer[1]);
	LCD_Position(1, 0);
	LCD_PrString(lcdBuffer[2]);
	LCD_Position(1, 8);
	LCD_PrString(lcdBuffer[3]);
}

void backlight(unsigned char toggle) {
	pinMode(2,7,1); // set the pin to strong
	if (toggle == 0) { BL_Data_ADDR=(BL_DataShadow&=~BL_MASK); }
	else if (toggle == 1) { BL_Data_ADDR=(BL_DataShadow|=BL_MASK); }
	else if (toggle == 2) { BL_Data_ADDR=(BL_DataShadow^=BL_MASK); }
}

// Sets the pin mode
void pinMode(unsigned char port, unsigned char pin, unsigned char state) {
	int i;
	BYTE bitMask = 1;
	for(i = 0; i < pin; i++) { bitMask *= 2; }

	switch (state) {
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
void digitalWrite(unsigned char port, unsigned char pin, unsigned char state) {
	int i ;
	BYTE bitMask = 1; 
	for(i = 0; i < pin; i++) { bitMask *= 2; }

	switch (state) {
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