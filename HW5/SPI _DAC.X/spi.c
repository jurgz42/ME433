#include <xc.h>           // processor SFR definitions
#include <sys/attribs.h>  // __ISR macro
#include "spi.h"
#include <math.h>

// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1
    
    // Turn of analog pins
    ANSELA = 0; //1 for analog
    ANSELB = 0;
    
    // Make an output pin for CS
    TRISBbits.TRISB2 = 0;   //Makes this an output pin for CS
    LATBbits.LATB2 = 1; //Makes this pin high        

    // Set SDO1
    RPA1Rbits.RPA1R = 0b0011; 
    // Set SDI1
    //SDI1Rbits.SDI1R = 0b0001;   //make sure to change

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    SPI1BRG = 100; // 1000 for 24kHz, 1 for 12MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.ON = 1; // turn on spi 
}

// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}

//given the channel and voltage, turns these value into a 16 bit number
//A: a_or_b = 0, B: a_or_b = 1
unsigned short make16(char a_or_b, unsigned char V) {
    unsigned short s = 0;
    s = s | (a_or_b << 15); //s = s ORR (a_or_b left shifted 15 bits)
    s = s | (0b111 << 12);  //s = s ORR (binary 111 left shifted 12 bits)
    s = s | (V << 4);   //s = s ORR (V left shifted 4 bits)
    return s;
}

//given the channel and voltage, sends 2 bytes
void send_spi(char a_or_b, unsigned char V) {
    unsigned short s = make16(a_or_b, V);
    LATBbits.LATB2 = 0; //CS low
    spi_io(s >> 8); //write first byte
    spi_io(s &  0xff); //write second byte
    LATBbits.LATB2 = 1; //CS high
}

//make sin function based on t
unsigned char make_sin(float t, float freq) {
    unsigned char x = (unsigned char) 127.5*sin(t*freq*2*3.1415) + 127.5;// 255sin(t * frequency) + 255
    return x;
}

//make triangle function based on t
unsigned char make_triangle(float t, float freq) {
    float n = 1./2./freq; //when each peak should occur
    float m = t/n;    //
    unsigned char x;
    
    if ((fmodf(m, 2)) < 1) {
        //ex result = 0.3
        // therefore slope should be positive
        x = (unsigned char) (255/n * fmodf(t,n));
    }
    else if (fmodf(m, 2) > 1) {
        //ex result = 1.3
        //therefore slope should be negative
        x = (unsigned char) (-255/n * fmodf(t,2*n) + 510);
    }
    else { //if odd
        x = 255;
    }
    return x;
}