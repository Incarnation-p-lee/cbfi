#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "global.h"
#include "data_structure.h"
#include "select_parameter.h"

void
select_parameter(int argc, char **argv)
{
  int count;

  if (2 > argc || NULL == argv)
  {
    print_usage();
    return;
  }

  init_conversion_instance();

  count = 1;
  while (count < argc)
  {
    if (!strcmp("-d", argv[count]))
      set_details_option();
    else if (!strncmp("-f", argv[count], 2))
    {
      count++;
      set_fixed_point(argv[count]);
    }
    else
      set_rawdata_input(argv[count]);

    count++;
  }
}

static void
init_conversion_instance(void)
{
  struct convert_attr *attr;

  attr = &instance.attr;
  attr->type = IEEE754;
  attr->opt = INT2FP;
  attr->bwidth = FLOAT_WIDTH_SINGLE;
  attr->detail = DISABLE_DETAIL;
  memset(instance.raw, 0, sizeof(instance.raw));
}

static inline void
set_details_option(void)
{
  struct convert_attr *attr;

  attr = &instance.attr;
  attr->detail = ENABLE_DETAIL;
}

static void
set_fixed_point(char *arg)
{
  char *tmp;
  int frac_bits;
  struct convert_attr *attr;
  struct fixed_point *fixed;

  tmp = arg;
  while (!isdigit(*tmp))
    tmp++;

  frac_bits = atoi(tmp);
  attr = &instance.attr;
  fixed = &instance.fixed;
  attr->type = FIXED;
  fixed->frac_bits = frac_bits;
}

static void
set_rawdata_input(char *arg)
{
  char *digit;
  enum operation type;
  unsigned long long data;
  struct convert_attr *attr;
  struct float_point *fpt;

  digit = arg;
  data = 0;
  attr = &instance.attr;
  fpt = &instance.fpt_set;
  type = is_input_data_float(digit);

  if (INT2FP == type && strncmp("0x", arg, 2) && strncmp("0X", arg, 2))
  {
    print_usage(); //never return here.
  }
  else if (INT2FP == type && (!strncmp("0x", arg, 2) || !strncmp("0X", arg, 2)))
  {
    digit = arg + 2;
    data = strtoull(digit, NULL, 16);
    attr->opt = INT2FP;
    set_float_bit_width(digit);
    store_int_data(data);
  }
  else if (FP2INT == type)
  {
    attr->opt = FP2INT;
    attr->bwidth = FLOAT_WIDTH_ALL;
    fpt->fpt_16 = strtof(digit, NULL);
    fpt->fpt_32 = strtof(digit, NULL);
    fpt->fpt_64 = strtod(digit, NULL);
  }
}

static void
set_float_bit_width(char *arg)
{
  struct convert_attr *attr;

  attr = &instance.attr;
  switch (strlen(arg))
  {
    case 16:
      attr->bwidth = FLOAT_WIDTH_DOUBLE;
      break;
    case 8:
      attr->bwidth = FLOAT_WIDTH_SINGLE;
      break;
    case 4:
      attr->bwidth = FLOAT_WIDTH_HALF;
      break;
    default:
      break;
  }
}

static inline void
store_int_data(unsigned long long data)
{
  *(unsigned long long *)instance.raw = data;
}

static enum operation
is_input_data_float(char *arg)
{
  register char *iter;

  iter = arg;
  while(*iter)
  {
    if('.' == *iter++)
      return FP2INT;
  }

  return INT2FP;
}
