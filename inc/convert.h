#ifndef CONVERT_H
#define CONVERT_H

extern void
print_ieee754_float_16(float *);
extern void
print_ieee754_float_32(float *);
extern void
print_ieee754_float_64(double *);
extern void
print_ieee754_int_16(unsigned *);
extern void
print_ieee754_int_32(unsigned *);
extern void
print_ieee754_int_64(unsigned long *);
extern void
print_ieee754_float_detail(void);
extern void
print_fixed_float_16(void *, unsigned);
extern void
print_fixed_float_32(void *, unsigned);
extern void
print_fixed_float_64(void *, unsigned);

#define PLUS_MIN_HALF_IN_SINGLE  0x33800000
#define MINUS_MIN_HALF_IN_SINGLE 0xb3800000
#define PLUS_MAX_HALF_IN_SINGLE  0x477fe000
#define MINUS_MAX_HALF_IN_SINGLE 0xc77fe000
#define DOUBLE_EXP_BITS_MASK     0x800fffffffffffffull

void
do_convert(void);
static void
ieee754_direction(void);
static void
ieee754_int2fp(void);
static void
ieee754_fp2int(void);
static void *
ieee754_half_to_single(unsigned);
static void *
ieee754_single_to_half(unsigned);
static signed
ieee754_is_NaN_half(unsigned);
static signed
ieee754_is_infi_half(unsigned);
static signed
ieee754_is_infi_single(unsigned);
static signed
ieee754_is_NaN_single(unsigned);
static unsigned
ieee754_is_single_to_half_overflow(unsigned);
static unsigned
bits_nozero_length(unsigned long);
static signed
convert_round(unsigned long long , enum FPRound_Mode);

static void
fixed_point_direction(void);
static void
fixed_point_fp2fd(void);
static inline void
fixed_point_fp2fd_peform(void *, double, unsigned, unsigned);
static inline void
fixed_point_set_sign(unsigned long long *, unsigned, unsigned);
static signed
is_fp2fd_overflow(double, unsigned, unsigned);
static void
fixed_point_fd2fp(void);

#endif
