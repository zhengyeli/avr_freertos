#include "app.h"

#pragma interrupt_handler int0_isr:iv_INT0
void int0_isr(void)
{
 //external interupt on INT0	   
 //printf("FSDFGS\n");
usart_transmit_str("ferdtgeryreg");
}

#pragma interrupt_handler int1_isr:iv_INT1
void int1_isr(void)
{
 //external interupt on INT1
 digital_showdata(7, 0xff);
}