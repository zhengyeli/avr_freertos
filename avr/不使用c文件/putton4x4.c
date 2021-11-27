#include "app.h"

unsigned char temp,temp1;

void key_init()
{
   DDRC  = 0xF0;
   PORTC = 0x0F;
}

void key_scan()     //�������ɨ��
{
   if (PINC != 0x0F)
   {
   	  temp1 = PINC;
      PORTC = 0xF0;
	  DDRC  = 0x0F;  
	  
	  if (PINC != 0XF0)
	  {
	    temp = temp1 | PINC;
	    key_num(temp);
	  }
	  else
	  {
	     key_init();
	  } 
   }
   else
   {
      key_init();
   }
}

void key_num(unsigned char key) //�����յ����βΣ�Ѱ�Ҷ�Ӧ������
{
 switch (key)           //�ж�
 {
  case 0xEE: digital_show_one_num(0,0);ENABLE_DIGITAL = 1;break; //show digital
  case 0xdE: digital_show_one_num(0,1);ENABLE_DIGITAL = 1;break;
  case 0xbE: digital_show_one_num(0,2);break;
  case 0x7E: digital_show_one_num(0,3);break;
  
  case 0xeD: digital_show_one_num(0,4);break;
  case 0xdD: digital_show_one_num(0,5);break;
  case 0xbD: digital_show_one_num(0,6);break;
  case 0x7D: digital_show_one_num(0,7);break;
  
  case 0xeB: digital_show_one_num(0,8);break;
  case 0xdB: digital_show_one_num(0,9);break;
  case 0xbB: digital_show_one_num(0,10);break;
  case 0x7B: digital_show_one_num(0,11);break;
  
  case 0xe7: digital_show_one_num(0,12);break;
  case 0xd7: digital_show_one_num(0,13);break;
  case 0xb7: digital_show_one_num(0,14);break;
  case 0x77: digital_show_one_num(0,15);break; 
 }
 key_init();
}
