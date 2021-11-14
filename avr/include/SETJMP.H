#ifndef __SETJMP_H
#define __SETJMP_H
#if defined(_HC11)
#define _JMPBUF_SIZ	3	/* pc, sp, x */
#elif defined(_HC12)
#define _JMPBUF_SIZ	4	/* page, pc, sp, x */
#elif defined(_HC16)
#define _JMPBUF_SIZ 4	/* pc ccr, sp, x */
#elif defined(_AVR)
#define _JMPBUF_SIZ 24
#elif defined(_MSP430)
#define _JMPBUF_SIZ 18
#elif defined(_ARM)
#define _JMPBUF_SIZ (11)	/* R4-R14 */
#else
#error "no target defined"
#endif

typedef int	jmp_buf[_JMPBUF_SIZ];
void longjmp(jmp_buf, int);
int setjmp(jmp_buf);
#endif
