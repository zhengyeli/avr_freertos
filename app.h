#ifndef APP_H
#define APP_H

#include "iom16v.h"
#include "macros.h"

#define  uchar unsigned char
#define  uint  unsigned int


extern int valid_num;
extern int shownum[]; 
extern char ENABLE_DIGITAL;

void EEPROMwriteString(int location, unsigned char *data, int len);
void EEPROMreadString(int location, unsigned char *data, int len);

#endif