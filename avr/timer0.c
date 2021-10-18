//TIMER0 initialize - prescale:1024
// WGM: CTC
// desired value: 1Hz
// actual value: Out of range

#include "app.h"

void timer0_init(void)
{
 TCCR0 = 0x00; //stop
 TCNT0 = 0x00 /*INVALID SETTING*/; //set count
 OCR0  = 0x00 /*INVALID SETTING*/;  //set compare
 TCCR0 = 0x0D; //start timer
}

#pragma interrupt_handler timer0_comp_isr:iv_TIM0_COMP
void timer0_comp_isr(void)
{
 //compare occured TCNT0=OCR0
}

#pragma interrupt_handler timer0_ovf_isr:iv_TIM0_OVF
void timer0_ovf_isr(void)
{
 TCNT0 = 0x00 /*INVALID SETTING*/; //reload counter value
}