#include "app.h"

static char index = 0;
static char count = 0;

char ENABLE_DIGITAL = 0;

//TIMER2 initialize - prescale:8
// WGM: CTC
// desired value: 1Hz
// actual value: Out of range

void timer2_init(void)
{
 TCCR2 = 0x00; //stop
 ASSR  = 0x00; //set async mode
 TCNT2 = 0x00; /*INVALID SETTING*/; //setup
 OCR2  = 0x10; /*INVALID SETTING*/;
 TCCR2 = 0x0A; //start
}

#pragma interrupt_handler timer2_comp_isr:iv_TIM2_COMP
void timer2_comp_isr(void)
{
 //compare occured TCNT2=OCR2
 if (count % 20 == 0 && ENABLE_DIGITAL == 1)
 {
   digital_show_one_num(index, shownum[index]);
   index++;
   if (index == valid_num) index = 0;
 }
 
 if (count == 125)
 {
    key_scan();
 }
 count++;
 if (count == 255) count = 0;
}

#pragma interrupt_handler timer2_ovf_isr:iv_TIM2_OVF
void timer2_ovf_isr(void)
{
 TCNT2 = 0x00 /*INVALID SETTING*/; //reload counter value
}