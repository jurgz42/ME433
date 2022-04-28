#ifndef I2C_MASTER_NOINT_H__
#define I2C_MASTER_NOINT_H__
// Header file for i2c_master_noint.c
// helps implement use I2C1 as a master without using interrupts

#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro

#define write_addy 0b01000000
#define read_addy 0b01000001
#define OLAT 0x0A   //set high or low
#define IODIR 0x00  //set input ot output
#define GPIO 0x09   //read input

void i2c_master_setup(void); // set up I2C1 as master
void i2c_master_start(void); // send a START signal
void i2c_master_restart(void); // send a RESTART signal
void i2c_master_send(unsigned char byte); // send a byte (either an address or data)
unsigned char i2c_master_recv(void); // receive a byte of data
void i2c_master_ack(int val); // send an ACK (0) or NACK (1)
void i2c_master_stop(void); // send a stop
void i2c_write(unsigned char reg, unsigned char val);   //write function
unsigned char i2c_read(unsigned char reg);

#endif