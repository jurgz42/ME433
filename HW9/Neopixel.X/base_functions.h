#ifndef BASE_FUNCTIONS_H__
#define BASE_FUNCTIONS_H__

#define PIC32_SYS_FREQ 48000000ul // 48 million Hz
#define PIC32_DESIRED_BAUD 230400 // Baudrate for RS232

void blink_LED();
void initialize();
void LED_On();
void LED_Off();
void delay(int);
void UART1_Startup(void);
void ReadUART1(char * string, int maxLength);
void WriteUART1(const char * string);

void blink();

float averagefunc(float gyro, float theta);

#endif