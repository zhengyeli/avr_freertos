#include "app.h"

//ADC initialize
// Conversion time: 1uS
int read_adc = 0;

void adc_init(void)
{
 ADCSR = 0x00; //disable adc
 ADMUX = 0x00; //select adc input 0
 ACSR  = 0x00;
 ADCSR = 0x89;
}

#pragma interrupt_handler adc_isr:iv_ADC
void adc_isr(void)
{
 //conversion complete, read value (int) using...
 // value=ADCL;            //Read 8 low bits first (important)
 // value|=(int)ADCH << 8; //read 2 high bits and shift into top byte
}


int start_adc(void)
{
     ADCSRA|=(1<<ADSC);           //ADC开始转换
	 while(!(ADCSRA&(1<<ADIF)));   //等待ADC转换结束
	 read_adc=ADC * 1000;                //获取ADC值                         
	 ADCSRA|=(1<<ADIF);           //清除ADC标志位
	 
	 return read_adc;    
}