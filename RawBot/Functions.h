/**************************
*  Function declarations  *
**************************/

void drive(unsigned char);
#define FORWARD 8
#define LEFT 4
#define RIGHT 6
#define BACKWARD 2
#define HALT 5 // Hammerzeit

void servoStart(unsigned int);
void servoStop(void);
void servoMove(int, unsigned int , unsigned int);

void usTrigSend(void);
unsigned long usCalculateDistance(unsigned long);

// LCD positions
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BTM_LEFT 2
#define BTM_RIGHT 3

void lcdAssign(long, unsigned int);
void lcdPrint(void);

void backlight(unsigned char);
void pinMode(unsigned char, unsigned char, unsigned char);
void digitalWrite(unsigned char, unsigned char, unsigned char);