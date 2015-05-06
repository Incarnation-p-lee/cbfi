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
                  "       -f frac_num, --fixed\n"
                  "              specific fixed point format\n");
  exit(EXIT_SUCCESS);
}

void
print_ieee754_float_16(float *fpt)
{
  fprintf(stdout, "half float point[16]:        ");
  fprintf(stdout, "%0.16f\n", *fpt);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_half_detail(instance.raw);
}

void
print_ieee754_float_32(float *fpt)
{
  fprintf(stdout, "single float point[32]:      ");
  fprintf(stdout, "%0.16f\n", *fpt);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_single_detail(instance.raw);
}

void
print_ieee754_float_64(double *dbl)
{
  fprintf(stdout, "double float point[64]:      ");
  fprintf(stdout, "%0.16f\n", *dbl);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_double_detail(instance.raw);
}

void
print_ieee754_int_16(unsigned *uint)
{
  fprintf(stdout, "half float point[16]:        ");
  fprintf(stdout, "%#04X\n", *uint);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_half_detail(instance.raw);
}

void
print_ieee754_int_32(unsigned *uint)
{
  fprintf(stdout, "single float point[32]:      ");
  fprintf(stdout, "%#08X\n", *uint);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_single_detail(&instance.fpt_set.fpt_32);
}

void
print_ieee754_int_64(unsigned long *ulong)
{
  fprintf(stdout, "double float point[64]:      ");
  fprintf(stdout, "%#016lX\n", *ulong);

  if (ENABLE_DETAIL == instance.attr.detail)
    print_ieee754_double_detail(&instance.fpt_set.fpt_64);
}

static inline void
print_ieee754_half_detail(void *data)
{
  struct ieee754_float_16 *f16;

  f16 = data;
  fprintf(stdout, "            Hexadecimal      Decimal          Binary\n");

  fprintf(stdout, "  |sign:    %016x %016u ", f16->sign, f16->sign);
  print_binary_bits(f16->sign, 1);

  fprintf(stdout, "  |exp :    %016x %016u ", f16->exp, f16->exp);
  print_binary_bits(f16->exp, 5);

  fprintf(stdout, "  |frac:    %016x %016u ", f16->fraction, f16->fraction);
  print_binary_bits(f16->fraction, 10);

  fprintf(stdout, "\n");
}

static inline void
print_ieee754_single_detail(void *data)
{
  struct ieee754_float_32 *f32;

  f32 = data;
  fprintf(stdout, "            Hexadecimal      Decimal          Binary\n");

  fprintf(stdout, "  |sign:    %016x %016u ", f32->sign, f32->sign);
  print_binary_bits(f32->sign, 1);

  fprintf(stdout, "  |exp :    %016x %016u ", f32->exp, f32->exp);
  print_binary_bits(f32->exp, 8);

  fprintf(stdout, "  |frac:    %016x %016u ", f32->fraction, f32->fraction);
  print_binary_bits(f32->fraction, 23);

  fprintf(stdout, "\n");
}


static inline void
print_ieee754_double_detail(void *data)
{
  struct ieee754_float_64 *f64;

  f64 = data;
  fprintf(stdout, "            Hexadecimal      Decimal          Binary\n");

  fprintf(stdout, "  |sign:    %016x %016u ", f64->sign, f64->sign);
  print_binary_bits(f64->sign, 1);

  fprintf(stdout, "  |exp :    %016x %016u ", f64->exp, f64->exp);
  print_binary_bits(f64->exp, 11);

  fprintf(stdout, "  |frac:    %016lx %016lu ",
    (unsigned long)f64->fraction, (unsigned long)f64->fraction);
  print_binary_bits(f64->fraction, 52);

  fprintf(stdout, "\n");
}


void
print_fixed_float_16(void *fixed, unsigned frac)
{
  fprintf(stdout, "half fixed point[16:%2u]:        ", frac);
  fprintf(stdout, "%#04X\n", *(unsigned*)fixed);
}

void
print_fixed_float_32(void *fixed, unsigned frac)
{
  fprintf(stdout, "single fixed point[32:%2u]:      ", frac);
  fprintf(stdout, "%#08X\n", *(unsigned*)fixed);
}

void
print_fixed_float_64(void *fixed, unsigned frac)
{
  fprintf(stdout, "double fixed point[64:%2u]:      ", frac);
  fprintf(stdout, "%#016llX\n", *(unsigned long long*)fixed);
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
