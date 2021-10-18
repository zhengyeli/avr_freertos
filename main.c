//ICC-AVR application builder : 2021/10/16 15:41:33
// Target : M16
// Crystal: 16.000Mhz

#include "app.h"

void delay(uint ms)
{
        uint i,j;
	   for(i=0;i<ms;i++)
	   {
	   for(j=0;j<1141;j++);
       }
}

void port_init(void)
{
 PORTA = 0x00;
 DDRA  = 0x00;
 PORTB = 0x00;
 DDRB  = 0x00;
 PORTC = 0x00; //m103 output only
 DDRC  = 0x00;
 PORTD = 0x00;
 DDRD  = 0x00;
 
 digital_port_init();
 
 key_init();
 
 uart0_port_init();

}


//call this routine to initialize all peripherals
void init_devices(void)
{
 //stop errant interrupts until set up
 CLI(); //disable all interrupts
 port_init();
 //watchdog_init();
 timer0_init();
 timer2_init();
 uart0_init();
 adc_init();
 
 MCUCSR |= 1 << JTD; //��ֹJTAG�ӿ�
 MCUCSR |= 1 << JTD; //��Ҫ�������β������ܱ���Чִ��

 MCUCR = 0x00;
 GICR  = 0xC0;
 TIMSK = 0xc7; //timer interrupt sources
 SEI(); //re-enable interrupts
 //all peripherals are now initialized
}

int main()
{
  int num = 0;
  init_devices();
  //num = start_adc();
  //key_scan();

 //RTEEPROMwrite(0X01,1);
 //num = RTEEPROMread(0x01);
 //digital_show_one_num(0,num);

  

  return 0;
}