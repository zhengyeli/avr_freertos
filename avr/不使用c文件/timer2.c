#include "app.h"

static char index = 0;
static char count = 0;

char ENABLE_DIGITAL = 1;

//TIMER2 initialize - prescale:8
// WGM: CTC
// desired value: 1Hz
// actual value: Out of range

//TIMER2 initialize - prescale:1024
// WGM: CTC
// desired value: 100Hz
// actual value: 98.892Hz (1.1%)
void timer2_init(void)
{
 TCCR2 = 0x00; //stop
 ASSR  = 0x00; //set async mode
 TCNT2 = 0xB2; //setup
 OCR2  = 0x4E;
 TCCR2 = 0x0F; //start
}

// 这种写法在avr-gcc不支持 需使用ISR(INT0_vect)
//#pragma interrupt_handler timer2_comp_isr:iv_TIM2_COMP

SIGNAL(TIMER2_COMP_vect)
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
   //usart_transmit_str("SCAN");
    key_scan();
 }
 count++;
 if (count == 255) count = 0;
}

//#pragma interrupt_handler timer2_ovf_isr:iv_TIM2_OVF
SIGNAL(TIMER2_OVF_vect)
{

 TCNT2 = 0xB2; //reload counter value
 // usart_transmit_str("999999999999");
}
