static void
ieee754_direction(void)
{
  switch (instance.attr.opt)
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
  void *tmp;

  tmp = instance.raw;
  switch(instance.attr.bwidth)
  {
    case FLOAT_WIDTH_HALF:
      tmp = ieee754_half_to_single(*(unsigned*)tmp);
      print_ieee754_float_16(tmp);
      break;
    case FLOAT_WIDTH_SINGLE:
      print_ieee754_float_32(tmp);
      break;
    case FLOAT_WIDTH_DOUBLE:
      print_ieee754_float_64(tmp);
      break;
    default:
      fprintf(stdout, "Unknown Float Point Width Detected.\n");
      break;
  }
}

static void
ieee754_fp2int(void)
{
  void *tmp;
  unsigned *data;
  struct float_point *fpt_set;

  fpt_set = &instance.fpt_set;
  tmp = &fpt_set->fpt_16;
  data = tmp;
  tmp = ieee754_single_to_half(*data);
  print_ieee754_int_16(tmp);

  tmp = &fpt_set->fpt_32;
  print_ieee754_int_32(tmp);

  tmp = &fpt_set->fpt_64;
  print_ieee754_int_64(tmp);
}

static void*
ieee754_half_to_single(unsigned data)
{
  struct ieee754_float_16 *fpt_16;
  struct ieee754_float_32 *result;
  void *tmp;
  unsigned sfp_exp, bias;

  tmp = &data;
  fpt_16 = tmp;
  tmp = &instance.fpt_set.fpt_16;
  result = tmp;

  result->sign = fpt_16->sign;
  if (ieee754_is_NaN_half(data))
  {
    result->exp = 0xff;
    result->fraction = fpt_16->fraction << 13;
  }
  else if (ieee754_is_infi_half(data))
  {
    result->exp = 0xff;
    result->fraction = 0x0;
  }
  else if (fpt_16->exp)
  {
    sfp_exp = fpt_16->exp - 15 + 127;
    result->exp = sfp_exp;
    result->fraction = fpt_16->fraction << (23 - 10);
  }
  else if (fpt_16->fraction)
  {
    sfp_exp = -14 + 127;
    bias = 10 - bits_nozero_length(fpt_16->fraction) + 1;
    sfp_exp -= bias;
    result->exp = sfp_exp;
    fpt_16->fraction = fpt_16->fraction << bias;
    result->fraction = fpt_16->fraction << (23 - 10);
  }
  else
  {
    result->exp = 0;
    result->fraction = 0;
  }

  return result;
}

static void*
ieee754_single_to_half(unsigned data)
{
  struct ieee754_float_32 *fpt_32;
  struct ieee754_float_16 *result;
  void *tmp;
  unsigned bias, frac;
  double real;
  unsigned long long *operand;

  bias = frac = 0;
  tmp = &data;
  fpt_32 = tmp;
  tmp = instance.raw;
  result = tmp;

  result->sign = fpt_32->sign;
  if (ieee754_is_NaN_single(data))
  {
    result->exp = 0x1f;
    result->exp = fpt_32->fraction >> 13;
  }
  else if (ieee754_is_infi_single(data))
  {
    result->exp = 0x1f;
    result->fraction = 0x0;
  }
  else if (!ieee754_is_single_to_half_overflow(data))
  {
    if (fpt_32->exp > 112)
    {
      result->exp = fpt_32->exp - 127 + 15;
      result->fraction = fpt_32->fraction >> 13;
      fpt_32->exp = 127 + 10;
    }
    else
    {
      result->exp = 0x0;
      bias = 126 - 14 - fpt_32->exp;
      result->fraction =
        (SET_BIT((fpt_32->fraction > 1), 22) >> 13) >> bias;
      fpt_32->exp = 10 - bias - 1 + 127;
    }
    real = (double)(*(float *)fpt_32);
    operand = (unsigned long long *)&real;
    if (convert_round(*operand, FPRound_TIAEVEN))
      *(unsigned *)result += 1;
  } else {
    printf("[34mWARNING[0m:Sp 2 Hp Overflow Occurs, Raw %#08X\n", data);
  }

  return result;
}

static unsigned
ieee754_is_single_to_half_overflow(unsigned data)
{
  float *tmp;
  void *result;
  unsigned plus_min, plus_max, minus_min, minus_max;

  tmp = (float*)&data;
  result = &((struct float_point*)instance.raw)->fpt_16;
  plus_min = PLUS_MIN_HALF_IN_SINGLE;
  plus_max = PLUS_MAX_HALF_IN_SINGLE;
  minus_min = MINUS_MIN_HALF_IN_SINGLE;
  minus_max = MINUS_MAX_HALF_IN_SINGLE;

  if (*tmp < *(float*)&plus_min && !GET_BIT(data, 31))
  {
    *(unsigned*)result = 0x0000;
    return 1;
  }
  else if (*tmp > *(float*)&plus_max && !GET_BIT(data, 31))
  {
    *(unsigned*)result = 0x7c00;
    return 1;
  }
  else if (*tmp > *(float*)&minus_min && GET_BIT(data, 31))
  {
    *(unsigned*)result = 0x8000;
    return 1;
  }
  else if (*tmp < *(float*)&minus_max && GET_BIT(data, 31))
  {
    *(unsigned*)result = 0xfc00;
    return 1;
  }

  return 0;
}

static signed
ieee754_is_NaN_half(unsigned data)
{
  struct ieee754_float_16 *fpt_16;

  fpt_16 = (struct ieee754_float_16*)&data;
  if (0x1f == fpt_16->exp && 0x0 != fpt_16->fraction)
    return 1;

  return 0;
}

static signed
ieee754_is_infi_half(unsigned data)
{
  struct ieee754_float_16 *fpt;

  fpt = (struct ieee754_float_16*)&data;
  if (0x1f == fpt->exp && 0x0 == fpt->fraction)
    return 1;

  return 0;
}

static signed
ieee754_is_NaN_single(unsigned data)
{
  struct ieee754_float_32 *fpt;

  fpt = (struct ieee754_float_32*)&data;
  if (0x1f == fpt->exp && 0x0 != fpt->fraction)
    return 1;

  return 0;
}

static signed
ieee754_is_infi_single(unsigned data)
{
  struct ieee754_float_32 *fpt;

  fpt = (struct ieee754_float_32*)&data;
  if (0x1f == fpt->exp && 0x0 == fpt->fraction)
    return 1;

  return 0;
}

static unsigned
bits_nozero_length(unsigned long frac)
{
  register unsigned len;

  len = 0;
  while (frac) {
    len++;
    frac >>= 1;
  }

  return len;
}

static signed
convert_round(unsigned long long data, enum FPRound_Mode mode)
{
  signed round_up;
  unsigned sign;
  double fpt, error;

  fpt = *(double*)&data;
  fpt = fpt > 0 ? fpt : - fpt;
  sign = (unsigned)GET_BIT(data, 63);
  error = fpt - (double)(unsigned long long)fpt;

  round_up = 0;
  switch (mode)
  {
    case FPRound_TIAEVEN:
      if (error > 0.5f ||
        (!(error > 0.5f || error < 0.5f) && 0x1 == ((unsigned)fpt & 0x1)))
        round_up = 1;
      break;
    case FPRound_TIAAWZERO:
      if (!(error < 0.5f))
        round_up = 1;
      break;
    case FPRound_ZERO:
      break;
    case FPRound_PINFI:
      if (error > 0.0f && !sign)
        round_up = 1;
      break;
    case FPRound_MINFI:
      if (error > 0.0f && sign)
        round_up = 1;
      break;
  }

  return round_up;
}

