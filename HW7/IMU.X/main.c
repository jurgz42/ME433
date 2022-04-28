#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro

#include <stdio.h>

#include "i2c_master_noint.h"
#include "base_functions.h"
#include "mpu6050.h"
#include <math.h>

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

int main() {
    initialize();   //initialize everything
    
    // init the imu
    init_mpu6050();
    
    char m_in[100]; // char array for uart data coming in
    char m_out[200]; // char array for uart data going out
    int i;
    #define dt 0.01
    //float ax[NUM_DATA_PNTS], ay[NUM_DATA_PNTS], az[NUM_DATA_PNTS], gx[NUM_DATA_PNTS], gy[NUM_DATA_PNTS], gz[NUM_DATA_PNTS], temp[NUM_DATA_PNTS];
    //float thetaxl[NUM_DATA_PNTS];

    
    //sprintf(m_out,"MPU-6050 WHO_AM_I: %X\r\n",whoami());
    //WriteUART1(m_out);
    char who = whoami(); // ask if the imu is there
    if (who != 0x68){
        // if the imu is not there, get stuck here forever
        while(1){
            LED_On();
        }
    }
    
    char IMU_buf[IMU_ARRAY_LEN]; // raw 8 bit array for imu data
    
    float ax, ay, az, gx, gz, thetaxl, thetazl;
    float pitch, yaw = 0;
    
    //ReadUART1(m_in,100); // wait for a newline
    
    while(1) {
        blink();
        burst_read_mpu6050(IMU_buf);
        ax = conv_xXL(IMU_buf);
        ay = conv_yXL(IMU_buf);
        az = conv_zXL(IMU_buf);
        gx = conv_xG(IMU_buf);
        gz = conv_zG(IMU_buf);
        
        thetaxl = atan2f(ax, az);
        thetazl = atan2f(az, ay);
 
        pitch += gx * dt;
        yaw += gz * dt;
        
        pitch = averagefunc(pitch, thetaxl);
        yaw = averagefunc(yaw, thetazl);
        
        sprintf(m_out, "Pitch: %f, Yaw: %f\r\n", pitch, yaw);
        WriteUART1(m_out);
        delay(dt);
    }
}

