#ifndef MAIN_H_    /* Guard against multiple inclusion */
#define MAIN_H_

void initialize();
void blink_LED();
void ReadUart1(char*, int);
void WriteUART1(const char*);

#endif /* MAIN_H_ */