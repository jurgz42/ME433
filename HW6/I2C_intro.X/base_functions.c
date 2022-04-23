#include <xc.h>
#include "base_functions.h"

void blink_LED() {
    LATAbits.LATA4 = 1;  //this turns on A4
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < 12000000) {
    //nothing, just keep looping
    }
    LATAbits.LATA4 = 0; //turns off A4
}

void LED_On() {
    LATAbits.LATA4 = 1;
}

void LED_Off() {
    LATAbits.LATA4 = 0;
}

void initialize() {
    __builtin_disable_interrupts(); // disable interrupts while initializing things

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    ///Initialization of pins
    //TRIS sets whether the pin is an input or output
    //LAT sets whether the pin is on or off
    TRISAbits.TRISA4 = 0;   //Makes A4 Output Pin
    LATAbits.LATA4 = 0;     //Turns off pin A4

    i2c_master_setup();
    
    __builtin_enable_interrupts();
}

void delay(int x) {
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT() < x) {}
}