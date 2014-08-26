#include <stdio.h>
#include <assert.h>
#include "global.h"
#include "data_structure.h"
#include "convert.h"

#include "ieee754_convert.c"
#include "fixed_point_convert.c"

void
do_convert(void)
{
  switch(instance.attr.type)
  {
    case IEEE754:
      ieee754_direction();
      break;
    case FIXED:
      fixed_point_direction();
      break;
    default:
      fprintf(stdout, "Unknown Encoding Class Type Detected.\n");
      break;
  }
}

