#include "app.h"
#include <stdio.h>

//#define USE_CUSTOM_PRINTF

void usart_transmit(unsigned char data) /*��������*/
{
    while (!(UCSRA & (1 << UDRE)))
        ;
    UDR = data;
}

void usart_transmit_str(char *data) /*�����ַ�������*/
{
    while (*data)
    {
        usart_transmit(*data);
        data++;
    }
    usart_transmit('\r');
}

#ifdef USE_CUSTOM_PRINTF
static char get_char(void)
{
    while (!(UCSRA & (1 << RXC)))
        ;
    return UDR;
}

static int put_char(char c)
{
    if (c == '\n')
        put_char('\r');
    // Wait for empty transmit buffer
    while (!(UCSRA & (1 << UDRE)))
        ;
    //Putting data into buffer , sends the data
    UDR = c;
    return 0;
}
// 变参函数自定义的printf函数
int printf(const char *fmt, ...)
{
    const char *s;
    int d;
    char buf[128];
    va_list ap;
    va_start(ap, fmt); // 将ap指向fmt（即可变参数的第一个?下一个？）
    while (*fmt)
    {
        if (*fmt != '%')
        {
            put_char(*fmt++); // 正常发送
            continue;
        }
        switch (*++fmt) // next %
        {
        case 's':
            s = va_arg(ap, const char *); // 将ap指向者转成char*型，并返回之
            for (; *s; s++)
                put_char(*s);
            break;
        case 'x':
            d = va_arg(ap, int); // 将ap指向者转成int型，并返回之
            itoa(d, buf, 16);    // 将整型d以16进制转到buf中
            for (s = buf; *s; s++)
                put_char(*s);
            break;
        case 'd':
            d = va_arg(ap, int);
            itoa(d, buf, 10); // 将整型d以10进制转到buf中
            for (s = buf; *s; s++)
                put_char(*s);
            break;
        default:
            put_char(*fmt);
            break;
        }
        fmt++;
    }
    va_end(ap);
    return 0;
}
/*
void myprintf(char *str,...)
{
char  buf[128];
unsigned char i = 0;
va_list ptr;
va_start(ptr,str);
vsprintf(buf,str,ptr);
while(buf[i])
{
     put_char(buf[i]);
     i++;
}
}
*/

#else
static char get_char(FILE *stream)
{
    while (!(UCSRA & (1 << RXC)))
        ;
    return UDR;
}

static int put_char(char c, FILE *stream)
{
    if (c == '\n')
        put_char('\r', stream);
    // Wait for empty transmit buffer
    while (!(UCSRA & (1 << UDRE)))
        ;
    //Putting data into buffer , sends the data
    UDR = c;
    return 0;
}
// this is use printf of stdio.h
FILE uartio = FDEV_SETUP_STREAM(put_char, get_char, _FDEV_SETUP_RW);

#endif

//UART0 initialize
// desired baud rate: 9600
// actual: baud rate:9615 (0.2%)
void uart0_init(void)
{
 UCSRB = 0x00; //disable while setting baud rate
 UCSRA = 0x00;
 UCSRC = BIT(URSEL) | 0x06;
 UBRRL = 0x33; //set baud rate lo
 UBRRH = 0x00; //set baud rate hi
 UCSRB = 0x98;

#ifndef USE_CUSTOM_PRINTF
    stdout = &uartio;
#endif
}
/*
//UART0 initialize
// desired baud rate: 115200
// actual: baud rate:125000 (7.8%)
// 使用115200输出空格误码
void uart0_init(void)
{
    UCSRB = 0x00; //disable while setting baud rate
    UCSRA = 0x00;
    UCSRC = BIT(URSEL) | 0x06;
    UBRRL = 0x03; //set baud rate lo
    UBRRH = 0x00; //set baud rate hi
                  //UCSRB = 0x98;
    UCSRB = (1 << RXEN) | (1 << TXEN);

#ifndef USE_CUSTOM_PRINTF
    stdout = &uartio;
#endif
}
*/
void uart0_port_init(void)
{
    DDRD |= 0X02;
    DDRD &= ~0X01;

    PORTD |= 0X02;
    PORTD |= 0X01;
}
/*
//#pragma interrupt_handler uart0_rx_isr:iv_USART0_RXC
SIGNAL(USARTRXC_vect)
{
    //uart has received a character in UDR
    printf("USARTRXC_vect\n");
}

//#pragma interrupt_handler uart0_tx_isr:iv_USART0_TXC
// UART IS FREE12313
SIGNAL(USARTTXC_vect)
{
    //character has been transmitted
    printf("USARTTXC_vect\n");
}
*/