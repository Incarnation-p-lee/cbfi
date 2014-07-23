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
                  "Usage: cbfi [-class] [-option] input\n"
                  "       -class: specific encoding, IEEE754 by default\n"
                  "             : -c0 IEEE754\n"
                  "       -option:\n"
                  "              :-d, show details\n"
                  "       input: integral, float[add .0 as suffix].\n\n");
  exit(EXIT_SUCCESS);
}

void
print_ieee754_float_32(float *fpt)
{
  fprintf(stdout, "32-bits float point:       ");
  fprintf(stdout, "%0.16f\n", *fpt);
}

void
print_ieee754_float_64(double *dbl)
{
  fprintf(stdout, "64-bits float point:       ");
  fprintf(stdout, "%0.16f\n", *dbl);
}

void
print_ieee754_int_32(unsigned *uint)
{
  fprintf(stdout, "32-bits float point:       ");
  fprintf(stdout, "%#08X\n", *uint);
}

void
print_ieee754_int_64(unsigned long *ulong)
{
  fprintf(stdout, "64-bits float point:       ");
  fprintf(stdout, "%#016lX\n", *ulong);
}

void
print_ieee754_float_detail(void)
{
  switch(instance.bwidth)
  {
    case FLOAT_WIDTH_SINGLE:
      instance.unpack.fpt_32 = instance.data;
      fprintf(stdout, "Sign:    %#016x  ",
        (unsigned)instance.unpack.fpt_32->sign);
      print_binary_bits(instance.unpack.fpt_32->sign, 1);
      fprintf(stdout, "Exp :    %#016x  ",
        (unsigned)instance.unpack.fpt_32->exp);
      print_binary_bits(instance.unpack.fpt_32->exp, 8);
      fprintf(stdout, "frac:    %#016x  ",
        (unsigned)instance.unpack.fpt_32->fraction);
      print_binary_bits(instance.unpack.fpt_32->fraction, 23);
      break;
    case FLOAT_WIDTH_DOUBLE:
      instance.unpack.fpt_64 = instance.data;
      fprintf(stdout, "Sign:    %#016x  ",
        (unsigned)instance.unpack.fpt_64->sign);
      print_binary_bits(instance.unpack.fpt_64->sign, 1);
      fprintf(stdout, "Exp :    %#016x  ",
        (unsigned)instance.unpack.fpt_64->exp);
      print_binary_bits(instance.unpack.fpt_64->exp, 11);
      fprintf(stdout, "frac:    %#016llx  ",
        (unsigned long long)instance.unpack.fpt_64->fraction);
      print_binary_bits(instance.unpack.fpt_64->fraction, 52);
      break;
    default:
      break;
  }
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
