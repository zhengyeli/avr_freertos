#ifndef __STDLIB_H
#define __STDLIB_H
#include <_const.h>

#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1
#ifndef NULL
#define NULL	0
#endif
#include <limits.h>
#define RAND_MAX	INT_MAX

#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned int size_t;
#endif

#if defined(_HC12)
#pragma nonpaged_function atof exit
#endif

/* ftoa function */
#define _FTOA_TOO_LARGE	-2	/* |input| > 2147483520 */
#define _FTOA_TOO_SMALL	-1	/* |input| < 0.0000001 */
/* ftoa returns static buffer of ~15 chars. If the input is out of
 * range, *status is set to either of the above #define, and 0 is
 * returned. Otherwise, *status is set to 0 and the char buffer is
 * returned.
 * This version of the ftoa is fast but cannot handle values outside
 * of the range listed. Please contact us if you need a (much) larger
 * version that handles greater ranges.
 * Note that the prototype differs from the earlier version of this
 * function. Example:
 *
 * int stat;
 * char *s = ftoa(123.45, &stat);
 * if (stat == 0)	// all OK!
 * 
 */
char *ftoa(float f, int *status);

#if defined(_AVR)
char *f2a(float f, int *status);
char *d2a(double d);
#endif

int abs(int);
long labs(long);
double atof(CONST char *);
int atoi(CONST char *);
long atol(CONST char *);
int rand(void);
void srand(unsigned);
long strtol(CONST char *, char **, int);
unsigned long strtoul(CONST char *, char **, int);

// base can be 2 to 36
char *ltoa(char *buf, long i, int base);
char *itoa(char *buf, int i, int base);
char *ultoa(char *buf, unsigned long i, int base);
char *utoa(char *buf, unsigned i, int base);

#if defined(_MSP430)
typedef struct { long quot; long rem; } ldiv_t;
typedef struct { int quot; int rem; } div_t;

ldiv_t ldiv(long a, long b);	// a/b and a%b
div_t div(int a, int b);	// a/b and a%b
#endif

#if !defined(_M8C)
void abort(void);
void *calloc(size_t, size_t);
void exit(int);
void free(void *);
void *malloc(size_t);
void *realloc(void *, size_t);

// usually call with _bss and and _bss+size_of_heap
void _NewHeap(void *start, void *end);
#if defined(_ARM)
// since C under ICCARM cannot access the _bss label easily, this is the
// help function to set up the heap. Just specify the size you want
void _SetHeapSize(unsigned size);
#endif
#endif

#endif

