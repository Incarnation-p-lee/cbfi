#ifndef CONVERT_H
#define CONVERT_H

extern void
print_ieee754_float_32(float *);
extern void
print_ieee754_float_64(double *);
extern void
print_ieee754_int_32(unsigned *);
extern void
print_ieee754_int_64(unsigned long *);

void
do_convert(void);
static void
ieee754_direction(void);
static void
ieee754_fp2int(void);
static void
ieee754_int2fp(void);

#endif
