#include <stdio.h>
#include <stdlib.h>
#include "print_set.h"


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
  fprintf(stdout, "32-bits float point:   ");
  fprintf(stdout, "%0.6f\n", *fpt);
}

void
print_ieee754_float_64(double *dbl)
{
  fprintf(stdout, "64-bits float point:   ");
  fprintf(stdout, "%0.15f\n", *dbl);
}

void
print_ieee754_int_32(unsigned *uint)
{
  fprintf(stdout, "32-bits float point:   ");
  fprintf(stdout, "%#08X\n", *uint);
}

void
print_ieee754_int_64(unsigned long *ulong)
{
  fprintf(stdout, "64-bits float point:   ");
  fprintf(stdout, "%#016lX\n", *ulong);
}
