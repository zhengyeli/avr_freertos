/* This putchar works with the M16 UART0. It will work with other devices
 * if their UART registers use the same names.  If the UART IO locations
 * are different from the M16, then you will also have to change the
 * #include header file statement.
 *
 * For device with multiple UARTs and if you want to use a different UART, 
 * change the IO register names as appropriate.
 */
#include "app.h"
 
int putchar(char c)
    {
    if ( c == '\n')
        putchar('\r');
    /* Wait for empty transmit buffer */
    while ( !(UCSRA & (1<<UDRE)) )
        ;                     
    /* Putting data into buffer , sends the data */
    UDR = c;  
    return c;
    }

