#include "iom16v.h"

void ADC_init(void)
{
 ADMUX = 0x40;//01 00 0000
 ADCSRA = 1<<ADEN|1<<ADSC| 0<<ADATE |0<<ADIF |0<<ADIE 
          |1<<ADPS2 |0<<ADPS1 |1<<ADPS0;
}

int start_adc(void)
{
     int read_adc = 0;
	 
     ADCSRA|=(1<<ADSC);           //ADC开始转换
	 while(!(ADCSRA&(1<<ADIF)));   //等待ADC转换结束
	 read_adc=ADC;                //获取ADC值                         
	 ADCSRA|=(1<<ADIF);           //清除ADC标志位
	 
	 return read_adc;    

}


/*mS延时函数*/
void delay_ms(unsigned int ms)
{unsigned int i,j;
for(i=0;i<ms;i++)
for(j=0;j<1141;j++);
}

void main(void)
{
 DDRA = 0x00;
 DDRB = 0XFF;
 ADC_init();
 while(1){
 PORTB = start_adc()*5/1024;
 delay_ms(100);
 
}}