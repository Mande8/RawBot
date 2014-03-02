/**************************
*  Function declarations  *
**************************/

void drive(unsigned char);
void servoStart(unsigned int);
void servoStop(void);
void servoMove(int, unsigned int , unsigned int);

void usTrigSend(void);
int usCalculateDistance(unsigned long);

void lcdAssign(long, unsigned int);
void lcdPrint(void);
#define LCD_TOP 0
#define LCD_BOTTOM 1


void backlight(unsigned char);
void pinMode(unsigned char, unsigned char, unsigned char);
void digitalWrite(unsigned char, unsigned char, unsigned char);