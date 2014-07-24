#include <stdio.h>
#include <assert.h>
#include "global.h"
#include "data_structure.h"
#include "convert.h"

void
do_convert(void)
{
  switch(instance.type)
  {
    case IEEE754:
      ieee754_direction();
      break;
    default:
      fprintf(stdout, "Unknown Encoding Class Type Detected.\n");
      break;
  }
}

static void
ieee754_direction(void)
{
  switch(instance.opt)
  {
    case FP2INT:
      ieee754_fp2int();
      break;
    case INT2FP:
      ieee754_int2fp();
      break;
    default:
      fprintf(stdout, "Unknown Operation Detected.\n");
      break;
  }
}

static void
ieee754_int2fp(void)
{
  switch(instance.bwidth)
  {
    case FLOAT_WIDTH_SINGLE:
      print_ieee754_float_32(instance.data);
      break;
    case FLOAT_WIDTH_DOUBLE:
      print_ieee754_float_64(instance.data);
      break;
    default:
      fprintf(stdout, "Unknown Float Point Width Detected.\n");
      break;
  }

  if (instance.detail)
    print_ieee754_float_detail();
}

static void
ieee754_fp2int(void)
{
  void *tmp;
  assert(FLOAT_WIDTH_ALL == instance.bwidth);

  tmp = &((struct float_point *)instance.data)->fpt_32;
  print_ieee754_int_32(tmp);
  tmp = &((struct float_point *)instance.data)->fpt_64;
  print_ieee754_int_64(tmp);

  if (instance.detail)
    print_ieee754_float_detail();
}
