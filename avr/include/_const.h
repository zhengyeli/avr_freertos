#ifndef __CONST_H
#define __CONST_H

 #if defined(_AVR) || defined(_M8C)
  #define FLASH __flash
  #if !defined(CONST)
    #define CONST const
  #endif
 #else
    #define CONST const
    #define FLASH const
 #endif

#endif
