#ifndef APP_H
#define APP_H

#include "iom16v.h"
#include <macros.h>

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <stdarg.h>
//#include <stdio.h>
//#include <macros.h>

#define  uchar unsigned char
#define  uint  unsigned int
#define  uint8 unsigned char
#define  uint16  unsigned int
#define  use_freertos 
#define  use_heap5 1

extern int valid_num;
extern int shownum[]; 
extern char ENABLE_DIGITAL;
  //printf("%d", temp);
  //num = start_adc();
  //RTEEPROMwrite(0X01,1);
//num = RTEEPROMread(0x01);
void EEPROMwriteString(int location, unsigned char *data, int len);
void EEPROMreadString(int location, unsigned char *data, int len);
#endif