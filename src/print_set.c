#include <stdio.h>
#include <stdlib.h>
#include "print_set.h"
#include "data_structure.h"
#include "global.h"


void
print_usage(void)
{
  fprintf(stdout, "Author: Incarnation P. Lee\n"
                  "        incarnation.p.lee@gmail.com\n\n"
                  "Usage: cbfi [OPTION]... [NUMERIC]\n\n"
                  "       -d, --detail\n"
                  "              show details of each field of float point.\n"
                  "       -f[not supported], --fixed\n"
                  "              specific fixed point format\n");
  exit(EXIT_SUCCESS);
}

void
print_ieee754_float_16(float *fpt)
{
  fprintf(stdout, "half float point[16]:         ");
  fprintf(stdout, "%0.16f\n", *fpt);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_half_detail(instance.raw);
}

void
print_ieee754_float_32(float *fpt)
{
  fprintf(stdout, "single float point[32]:       ");
  fprintf(stdout, "%0.16f\n", *fpt);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_single_detail(instance.raw);
}

void
print_ieee754_float_64(double *dbl)
{
  fprintf(stdout, "double float point[64]:       ");
  fprintf(stdout, "%0.16f\n", *dbl);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_double_detail(instance.raw);
}

void
print_ieee754_int_16(unsigned *uint)
{
  fprintf(stdout, "half float point[16]:         ");
  fprintf(stdout, "%#04X\n", *uint);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_half_detail(instance.raw);
}

void
print_ieee754_int_32(unsigned *uint)
{
  fprintf(stdout, "single float point[32]:       ");
  fprintf(stdout, "%#08X\n", *uint);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_single_detail(&instance.fpt_set.fpt_32);
}

void
print_ieee754_int_64(unsigned long *ulong)
{
  fprintf(stdout, "double float point[64]:       ");
  fprintf(stdout, "%#016lX\n", *ulong);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_double_detail(&instance.fpt_set.fpt_64);
}

static inline void
print_ieee754_half_detail(void *data)
{
  struct ieee754_float_16 *f16;

  f16 = data;
  fprintf(stdout, "  |sign:    %#016x  ", f16->sign);
  print_binary_bits(f16->sign, 1);

  fprintf(stdout, "  |exp :    %#016x  ", f16->exp);
  print_binary_bits(f16->exp, 5);

  fprintf(stdout, "  |frac:    %#016x  ", f16->fraction);
  print_binary_bits(f16->fraction, 10);

  fprintf(stdout, "\n");
}

static inline void
print_ieee754_single_detail(void *data)
{
  struct ieee754_float_32 *f32;

  f32 = data;
  fprintf(stdout, "  |sign:    %#016x  ", f32->sign);
  print_binary_bits(f32->sign, 1);

  fprintf(stdout, "  |exp :    %#016x  ", f32->exp);
  print_binary_bits(f32->exp, 8);

  fprintf(stdout, "  |frac:    %#016x  ", f32->fraction);
  print_binary_bits(f32->fraction, 23);

  fprintf(stdout, "\n");
}


static inline void
print_ieee754_double_detail(void *data)
{
  struct ieee754_float_64 *f64;

  f64 = data;
  fprintf(stdout, "  |sign:    %#016x  ", f64->sign);
  print_binary_bits(f64->sign, 1);

  fprintf(stdout, "  |exp :    %#016x  ", f64->exp);
  print_binary_bits(f64->exp, 11);

  fprintf(stdout, "  |frac:    %#016lx  ", (unsigned long)f64->fraction);
  print_binary_bits(f64->fraction, 52);

  fprintf(stdout, "\n");
}

static void
print_binary_bits(unsigned long data, unsigned size)
{
  while (size-- > 0)
  {
    if ((data >> size) & 0x1ull)
      fprintf(stdout, "1");
    else
      fprintf(stdout, "0");
  }
  fprintf(stdout, "B\n");
}
