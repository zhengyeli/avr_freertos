#include "app.h"

//Watchdog initialize
// prescale: 16K 
void watchdog_init(void)
{
 WDR(); //this prevents a timout on enabling
 WDTCR = 0x08; //WATCHDOG ENABLED - dont forget to issue WDRs
}