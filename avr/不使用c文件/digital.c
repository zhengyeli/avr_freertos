#include "app.h"

const unsigned char table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
		           0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
int valid_num = 8;
int shownum[8]   = {1,2,3,4,5,6,7,8};
   
				   
void digital_port_init()
{
 	DDRA |= 0X07;
	PORTA &= ~0X07;
	 
	DDRB = 0XFF;
	PORTB = 0Xff;
}

void digital_show_one_num(unsigned char index, unsigned char num)
{
     PORTB = ~0x00;
 	 switch (index)
	 {
	  	case 0: PORTA &= ~0x07;break;
		default:PORTA = ((PINA & 0XF8) | index);		
	 }
	 PORTB = ~table[num];
	 //PORTB = ~num;
}

void digital_showdata(unsigned char index, unsigned char data)
{
     PORTB = ~0x00;
 	 switch (index)
	 {
	  	case 0: PORTA &= ~0x07;break;
		default:PORTA = ((PINA & 0XF8) | index);		
	 }
	 PORTB = ~data;
	 //PORTB = ~num;
}