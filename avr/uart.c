#include "app.h"

static unsigned char rxdata[8] = {0};
static unsigned char index = 0;

//UART0 initialize
// desired baud rate: 115200
// actual: baud rate:125000 (7.8%)
void uart0_init(void)
{
 UCSRB = 0x00; //disable while setting baud rate
 UCSRA = 0x00;
 UCSRC = BIT(URSEL) | 0x06;
 UBRRL = 0x03; //set baud rate lo
 UBRRH = 0x00; //set baud rate hi
 UCSRB = 0x98;
}

void uart0_port_init(void)
{
  DDRD |= 0X02;
  DDRD &= ~0X01;
  
  PORTD |= 0X02;
  PORTD |= 0X01;
}

//#pragma interrupt_handler uart0_rx_isr:iv_USART0_RXC
ISR(_VECTOR(11))
{
 //uart has received a character in UDR
  DDRA ^= 0XA0;
 PORTA ^= 0XA0;
 while ( !(UCSRA & (1<<RXC)) );
 index =  UDR;
 DDRA ^= 0XA0;
 PORTA ^= 0XA0;
 //send back
}

//#pragma interrupt_handler uart0_tx_isr:iv_USART0_TXC
// UART IS FREE
ISR(_VECTOR(15))
{
 //character has been transmitted
  DDRA = 0X40;
 PORTA = 0X40;
}

// UART IS SEND
ISR(_VECTOR(13))
{
 //character has been transmitted
  DDRA = 0X80;
 PORTA = 0X80;
}

void usart_transmit(unsigned char data) /*��������*/
{
 while(!(UCSRA&(1<<UDRE)));
 UDR = data;
}

void usart_transmit_str(char *data) /*�����ַ�������*/
{
 while(*data)
 {
  usart_transmit(*data);
  data++;
  }
}

