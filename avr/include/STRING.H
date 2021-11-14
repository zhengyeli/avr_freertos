/* modified by ja */

#ifndef __STRING_H
#define __STRING_H
#include <_const.h>

#if defined(_HC12)
#pragma nonpaged_function strcpy
#endif

#if defined(_M8C) && defined(_LMM)
#define strcpy	strcpyLMM
#define cstrcpy	cstrcpyLMM
#define strcmp	strcmpLMM
#define	cstrcmp	cstrcmpLMM
#define	strlen	strlenLMM
#define	cstrlen	cstrlenLMM
#define	strcat	strcatLMM
#define	cstrcat	cstrcatLMM
#endif

#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned int size_t;
#endif

void *memcpy(void *, CONST void *, size_t);
void *memset(void *, int, size_t);
void *memchr(void *, int, size_t);
int memcmp(void *, void *, size_t);
void *memmove(void *, CONST void *, size_t);

char *strchr(CONST char *, int);
int strcoll(CONST char *, CONST char *);
size_t strcspn(CONST char *, CONST char *);
char *strncat(char *, CONST char *, size_t);
int strncmp(CONST char *, CONST char *, size_t);
char *strncpy(char *, CONST char *, size_t);
char *strpbrk(CONST char *, CONST char *);
char *strrchr(CONST char *, int);
size_t strspn(CONST char *, CONST char *);
char *strstr(CONST char *, CONST char *);

#if !defined(_M8C)
char *strtok(char *, CONST char *);
#endif

size_t strlen(CONST char *);
char *strcpy(char *, CONST char *);
int strcmp(CONST char *, CONST char *);
char *strcat(char *, CONST char *);

#if defined(_AVR) || defined(_M8C)
size_t cstrlen(__flash char *cs);
char *cstrcpy(char *, __flash char *cs);
char *cstrncpy(char *, __flash char *cs, size_t);
int cstrcmp(__flash char *cs, char *);
char *cstrcat(char *, __flash char *);
#endif

/**/
#if defined(_AVR)
/* need to add prototypes to HELP file */
void *cmemcpy(void *, __flash void *, size_t);
void *cmemchr(__flash void *, int, size_t);
int cmemcmp(__flash void *, void *, size_t);
char *cstrncat(char *, __flash char *cs, size_t);
int cstrncmp(__flash char *cs, char *, size_t);
size_t cstrcspn(char *, __flash char *cs);
size_t cstrspn(char *, __flash char *cs);
char *cstrstr(char *, __flash char *cs);
char *cstrpbrk(char *, __flash char *cs);
/**/
/* and now the ones using ELPM */
/**/
void *cmemcpyx(void *, __flash void *, size_t);
void *cmemchrx(__flash void *, int, size_t);
int cmemcmpx(__flash void *, void *, size_t);
char *cstrcatx(char *, __flash char *);
char *cstrncatx(char *, __flash char *, size_t);
int cstrcmpx(__flash char *cs, char *i);
int cstrncmpx(__flash char *cs, char *i, size_t);
char *cstrcpyx(char *, __flash char *cs);
char *cstrncpyx(char *, __flash char *cs, size_t);
size_t cstrcspnx(char *, __flash char *cs);
size_t cstrlenx(__flash char *cs);
size_t cstrspnx(char *, __flash char *cs);
char *cstrstrx(char *, __flash char *cs);
char *cstrpbrkx(char *, __flash char *cs);
char *cstrtok(char *, __flash char *);
/**/

#endif

/*
size_t strxfrm(char *, char *, size_t);
*/
#endif
