/* This putchar works with the M16 UART0. It will work with other devices
 * if their UART registers use the same names.  If the UART IO locations
 * are different from the M16, then you will also have to change the
 * #include header file statement.
 *
 * For device with multiple UARTs and if you want to use a different UART, 
 * change the IO register names as appropriate.
 */
#include "app.h"
#include "STDIO.H"
#include "STDLIB.H"


int putchar(char c)
{
    if (c == '\n')
        putchar('\r');
    // Wait for empty transmit buffer 
    while ( !(UCSRA & (1<<UDRE)) )
        ;                     
    //Putting data into buffer , sends the data
    UDR = c;  
    return c;
}
/*
void myprintf(char* fmt,...)  
{  
    const char* s;  
    int d;  
    char buf[16];  
    va_list ap;  
    va_start(ap,fmt);   // 将ap指向fmt（即可变参数的第一个?下一个？）  
    while (*fmt)  
    {  
        if (*fmt != '%')  
        {  
            putchar(*fmt++);   // 正常发送  
            continue;     
        }  
        switch (*++fmt) // next %  
        {  
        case 's':  
            s = va_arg(ap,const char*); // 将ap指向者转成char*型，并返回之  
            for (; *s; s++)  
                putchar(*s);  
            break;  
        case 'x':  
            d = va_arg(ap,int);     // 将ap指向者转成int型，并返回之  
            itoa(d,buf,16);         // 将整型d以16进制转到buf中  
            for (s = buf; *s; s++)  
                putchar(*s);  
            break;  
        case 'd':  
            d = va_arg(ap,int);  
            itoa(d,buf,10);         // 将整型d以10进制转到buf中  
            for (s = buf; *s; s++)  
                putchar(*s);  
            break;  
        default:  
            putchar(*fmt);  
            break;  
        }  
        fmt++;  
    }  
    va_end(ap);  
}

void Uart0_printf(char *str,...)
{
 char  buf[128];
 unsigned char i = 0;
 va_list ptr;
 va_start(ptr,str);
 vsprintf(buf,str,ptr);
 while(buf[i])
 {
     putchar(buf[i]);
     i++;
 }
}

*/