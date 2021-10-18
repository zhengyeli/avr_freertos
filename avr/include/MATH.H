#ifndef __MATH_H
#define __MATH_H

#define _PI	3.1415926535897932f

float acosf(float x);
float asinf(float x);
float atan2f(float y, float x);
float atanf(float x);
float ceilf(float y);
float cosf(float x);
float coshf(float x);
float exp10f(float x);
float expf(float x);
float fabsf(float x);
float floorf(float y);
float fmodf(float y, float z);
float frexpf(float x, int *eptr);
float froundf(float d);
float ldexpf(float d, int n);
float log10f(float x);
float logf(float x);
float modff(float y, float *i);
float powf(float x,float y);
float sinf(float x);
float sinhf(float x);
float sqrtf(float x);
float tanf(float x);
float tanhf(float x);

#if defined(_ARM)
/* double not yet supported
double acos(double x);
double asin(double x);
double atan2(double y, double x);
double atan(double x);
double ceil(double y);
double cos(double x);
double cosh(double x);
double exp10(double x);
double exp(double x);
double fabs(double x);
double floor(double y);
double fmod(double y, double z);
double frexp(double x, int *eptr);
double fround(double d);
double ldexp(double d, int n);
double log10(double x);
double log(double x);
double modf(double y, double *i);
double pow(double x,double y);
double sin(double x);
double sinh(double x);
double sqrt(double x);
double tan(double x);
double tanh(double x);
*/
#else

#define acos	 acosf
#define asin	 asinf
#define atan2	 atan2f
#define atan	 atanf
#define ceil	 ceilf
#define cos	 cosf
#define cosh	 coshf
#define exp10	 exp10f
#define exp	 expf
#define fabs	 fabsf
#define floor	 floorf
#define fmod	 fmodf
#define frexp	 frexpf
#define fround	 froundf
#define ldexp	 ldexpf
#define log10	 log10f
#define log	 logf
#define modf	 modff
#define pow	 powf
#define sin	 sinf
#define sinh	 sinhf
#define sqrt	 sqrtf
#define tan	 tanf
#define tanh	 tanhf
#endif

#endif
