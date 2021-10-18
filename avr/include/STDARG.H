#ifndef __STDARG_H
#define __STDARG_H
typedef char *va_list;

// AVR/430/ARM needs to round up any char (and short for ARM) arguments to
// the next 2/4 byte boundary. HC12 does not need that since it is a Big
// Endian machine and the char argument is in the higher address within the
// word
#if defined(_AVR) || defined(_MSP430)
  #define va_start(ap, last_arg)	\
	(ap = ((char *)&last_arg + ((sizeof(last_arg)+1)&~1)))
#elif defined(_HC12)
  #define va_start(ap, last_arg)	\
	(ap = ((char *)&last_arg + sizeof(last_arg)))

#elif defined(_ARM) || defined(_PROP)
  #define va_start(ap, last_arg)	\
	(ap = ((char *)&last_arg + ((sizeof(last_arg)+3)&~3)))
#else

char *_va_start(void *, int);
#define va_start(ap, last_arg)	\
	(ap = _va_start(&last_arg, sizeof(last_arg)))
#endif

#define va_arg(ap, type)	(ap += sizeof (type), ((type *)ap)[-1])
#define va_end(ap)
#endif
