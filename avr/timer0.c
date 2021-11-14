//TIMER0 initialize - prescale:1024
// WGM: CTC
// desired value: 1Hz
// actual value: Out of range
#include "app.h"

//TIMER0 initialize - prescale:1024
// WGM: CTC
// desired value: 100Hz
// actual value: 98.892Hz (-1.1%)
void timer0_init(void)
{
 TCCR0 = 0x00; //stop
 TCNT0 = 0xB2; //set count
 OCR0  = 0x4E;  //set compare
 TCCR0 = 0x0D; //start timer
}


 #ifndef use_freertos
//#pragma interrupt_handler timer0_comp_isr:iv_TIM0_COMP
SIGNAL(TIMER0_OVF_vect)
{
    TCNT0 = 0xB2; //reload counter value
    //usart_transmit_str("77777777");
}

SIGNAL(TIMER0_COMP_vect)
{
     //compare occured TCNT0=OCR0
    //usart_transmit_str("3333333333333");
}
#endif