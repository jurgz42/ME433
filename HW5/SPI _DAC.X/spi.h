#ifndef SPI__H__    //Guard against multiple inclusion
#define SPI__H__

void initSPI();
unsigned char spi_io(unsigned char o);
unsigned short make16(char a_or_b, unsigned char V);
void send_spi(char a_or_b, unsigned char V);
unsigned char make_sin(float t, float freq);
unsigned char make_triangle(float t, float freq);

#endif // SPI__H__