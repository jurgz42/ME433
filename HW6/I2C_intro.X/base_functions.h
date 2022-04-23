#ifndef BASE_FUNCTIONS_H__
#define BASE_FUNCTIONS_H__

#include "i2c_master_noint.h"

void blink_LED();
void initialize();
void LED_On();
void LED_Off();
void delay(int);
void WriteUART1(const char *);

#endif