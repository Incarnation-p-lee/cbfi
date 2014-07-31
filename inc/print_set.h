#ifndef PRINT_USAGE_H
#define PRINT_USAGE_H

void
print_usage(void);
void
print_ieee754_float_16(float *);
void
print_ieee754_float_32(float *);
void
print_ieee754_float_64(double *);
void
print_ieee754_int_16(unsigned *);
void
print_ieee754_int_32(unsigned *);
void
print_ieee754_int_64(unsigned long *);
static inline void
print_ieee754_half_detail(void *);
static inline void
print_ieee754_single_detail(void *);
static inline void
print_ieee754_double_detail(void *);
static void
print_binary_bits(unsigned long, unsigned);

#endif
