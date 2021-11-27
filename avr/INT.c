#include "app.h"


void int_port_init(void)
{
    DDRD &= ~0X0C;
    PORTD |= 0X0C;
}

//#pragma interrupt_handler int0_isr:iv_INT0
ISR(_VECTOR(1))
{
 //usart_transmit_str("11111111111111");
}

//#pragma interrupt_handler int1_isr:iv_INT1
ISR(_VECTOR(2))
{
 //usart_transmit_str("22222222222222");
}