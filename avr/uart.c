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
 UCSRC = BIT(URSEL) | 0x07;
 UBRRL = 0x08; //set baud rate lo
 UBRRH = 0x00; //set baud rate hi
 UCSRB = 0xF8;
}

void uart0_port_init(void)
{
  DDRD |= 0X02;
  DDRD &= ~0X01;
  
  PORTD |= 0X02;
  PORTD |= 0X01;
}

#pragma interrupt_handler uart0_rx_isr:iv_USART0_RXC
void uart0_rx_isr(void)
{
 //uart has received a character in UDR
 /* 等待接收数据 */
 while ( !(UCSRA & (1<<RXC)) );
 /* 从缓冲器中获取并返回数据 */
 index =  UDR;
 usart_transmit_str(index);
 //send back
 
}

#pragma interrupt_handler uart0_udre_isr:iv_USART0_UDRE
void uart0_udre_isr(void)
{
 //character transferred to shift register so UDR is now empty
}

#pragma interrupt_handler uart0_tx_isr:iv_USART0_TXC
void uart0_tx_isr(void)
{
 //character has been transmitted
 digital_show_one_num(4, 5);
}


void usart_transmit(unsigned char data) /*发送数据*/
{
 while(!(UCSRA&(1<<UDRE)));
 UDR = data;
}

void usart_transmit_str(char *data) /*发送字符串数据*/
{
 while(*data)
 {
  usart_transmit(*data);
  data++;
  }
}

