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
    else if (!strncmp("-c", argv[count], 2))
      set_encoding_class(argv[count]);
    else
      set_rawdata_input(argv[count]);
    count++;
  }
}

static void
init_conversion_instance(void)
{
  instance.type = IEEE754;
  instance.opt = INT2FP;
  memset(instance.raw, 0, sizeof(instance.raw));
  instance.bwidth = FLOAT_WIDTH_SINGLE;
  instance.detail = DETAIL_DISABLED;
  instance.data = instance.raw;
}

static inline void
set_details_option(void)
{
  instance.detail = DETAIL_ENABLED;
}

static void
set_encoding_class(char *arg)
{
  char *tmp;
  int class;

  tmp = arg;
  while (isdigit(tmp))
    tmp++;

  class = atoi(tmp);
  switch (class)
  {
    case IEEE754:
      instance.type = IEEE754;
      break;
    default:
      instance.type = IEEE754;
      break;
  }
}

static void
set_rawdata_input(char *arg)
{
  char *digit;
  unsigned long long data;

  digit = arg;
  data = 0;
  if (!strncmp("0x", arg, 2) || !strncmp("0X", arg, 2))
  {
    digit = arg + 2;
    instance.opt = INT2FP;
    instance.data = instance.raw;
    data = strtoll(digit, NULL, 16);
  }
  else
  {
    if (FP2INT == is_input_data_float(digit))
    {
      instance.opt = FP2INT;
      instance.fpt_set.fpt_32 = strtof(digit, NULL);
      instance.fpt_set.fpt_64 = strtod(digit, NULL);
      instance.bwidth = FLOAT_WIDTH_ALL;
      instance.data = &instance.fpt_set;
      return;
    }
    else
      data = strtoll(digit, NULL, 10);
  }

  store_raw_data(data);
}

static void
store_raw_data(unsigned long long data)
{
  if (data > UINT_MAX)
  {
    instance.bwidth = FLOAT_WIDTH_DOUBLE;
    *(unsigned long long *)instance.raw = data;
  }
  else
  {
    instance.bwidth = FLOAT_WIDTH_SINGLE;
    *(unsigned *)instance.raw = (unsigned)data;
  }
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
