/* This getchar works with M16 and all the AVRs that share the
 * same IO locations for USR and UDR
 *
 * For example for other devices, look at the examples for putchar_????.c
 */
#include "app.h"

int getchar(void)
    {
    while ((UCSRA & 0x80) == 0)
        ;
    return UDR;
    }
