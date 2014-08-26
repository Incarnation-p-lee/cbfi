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
void
print_fixed_float_16(void *, unsigned);
void
print_fixed_float_32(void *, unsigned);
void
print_fixed_float_32(void *, unsigned);

static inline void
print_ieee754_half_detail(void *);
static inline void
print_ieee754_single_detail(void *);
static inline void
print_ieee754_double_detail(void *);
static void
print_binary_bits(unsigned long, unsigned);

#endif
