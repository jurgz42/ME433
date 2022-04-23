#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <stdio.h>

#include "i2c_master_noint.h"
#include "base_functions.h"


// DEVCFG0
#pragma config DEBUG = OFF // disable debugging
#pragma config JTAGEN = OFF // disable jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // disable flash write protect
#pragma config BWP = OFF // disable boot write protect
#pragma config CP = OFF // disable code protect

// DEVCFG1
#pragma config FNOSC = FRCPLL // use fast frc oscillator with pll
#pragma config FSOSCEN = OFF // disable secondary oscillator
#pragma config IESO = OFF // disable switching clocks
#pragma config POSCMOD = OFF // primary osc disabled
#pragma config OSCIOFNC = OFF // disable clock output
#pragma config FPBDIV = DIV_1 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD // disable clock switch and FSCM
#pragma config WDTPS = PS1048576 // use largest wdt value
#pragma config WINDIS = OFF // use non-window mode wdt
#pragma config FWDTEN = OFF // wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz fast rc internal oscillator
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz

// DEVCFG3
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations

#define DESIRED_BAUD 230400    // Baudrate for RS232


int main() {
    //i2c_master_setup();
    initialize();
    i2c_write(IODIR, 0b01111111);   //0 is output, 1 is input
    //now GPIO7 = output, GPIO0 = input
    i2c_write(OLAT, 0b00000000);    //0 is low, 1 is high
    //now GPIO7 = low, while all other pins equal high
    unsigned char x = 1;
    while (1) {
        LED_On();
        x = i2c_read(GPIO); //read the inputs
        x = x & 0b1;    //we only check GPIO0
        
        if (x == 0) {   //if input is low
            i2c_write(OLAT, 0b10000000);    //turn on led
            delay(12000000);
            i2c_write(OLAT, 0b00000000);  //turn off led
        }
        
        delay(12000000);
        LED_Off();
        delay(12000000);
    }
}