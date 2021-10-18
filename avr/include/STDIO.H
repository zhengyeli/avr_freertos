#ifndef __STDIO_H
#define __STDIO_H
#include <stdarg.h>
#include <_const.h>

#if defined(_AVR) || defined(_HC12)
/* device specific functions map to special name forms so the linker
 * can give more meaningful error messages
 */
#pragma device_specific_function putchar getchar
#endif

#if defined(_HC12)
#pragma nonpaged_function putchar getchar
#endif

int getchar(void);
int putchar(char);
char *gets(char *);
#ifdef _M8C
int puts(char *);
#else
int puts(CONST char *);
#endif
int printf(CONST char *, ...);
int vprintf(CONST char *, va_list va);
int sprintf(char *, CONST char *, ...);
int vsprintf(char *, CONST char *, va_list va);

int scanf(CONST char *, ...);
int vscanf(CONST char *, va_list va);
int sscanf(char *, CONST char *, ...);
int vsscanf(char *, CONST char *, va_list va);

#ifndef NULL
#define NULL 0
#endif

#if defined(_AVR)
int cputs(FLASH char *);
int cscanf(FLASH char *, ...);
int csscanf(char *, FLASH char *, ...);
int cprintf(FLASH char *, ...);
int csprintf(char *, FLASH char *, ...);
#endif

#endif
