#ifndef		__SPI__H
#define		__SPI__H

#if !defined(_AVR)
#error "This file should only be used with ICCV7 for AVR"
#endif
/* SPI header for AVR */
/* use the AppBuilder to generate spi_init function!! */

void SpiWriteByte(unsigned char);
unsigned char SpiReadByte(void);
unsigned char SpiReadDataReg(void);


/*
**  End of Header file
*/
#endif
