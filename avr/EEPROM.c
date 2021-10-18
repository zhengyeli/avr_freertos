#include "app.h"

void RTEEPROMwrite(int location, unsigned char databyte)
{
	unsigned char savedSREG;
    while(EECR && 0x02);
	EEAR = location;								// set address
	EEDR = databyte;								// set data	
	savedSREG = SREG;								// keep setting so it can be restored
	CLI();													// disable interrupts
	EECR |= BIT(EEMWE);							// set "write enable" bit
	EECR |= BIT(EEWE);							// set "write" bit
	SREG = savedSREG;								// restore SREG
	EEAR = 0;
}



// function to read from the EEPROM
// reads a byte from the specified location
// this will fail if the EEPROM is not ready!
unsigned char RTEEPROMread(int location)
{
    while(EECR && 0x02);
	EEAR = location;								// set address
	EECR |= BIT(EERE);							// set "read enable" bit
	EEAR = 0;
	return (EEDR);
}



