static void
fixed_point_direction(void)
{
  switch (instance.attr.opt)
  {
    case FP2INT:
      fixed_point_fp2fd();
      break;
    case INT2FP:
      //fixed_point_fd2fp();
      break;
    default:
      fprintf(stdout, "Unknown Operation Detected.\n");
      break;
  }
}

static void
fixed_point_fp2fd(void)
{
  double fp;
  struct fixed_point *fd;
  unsigned frac_bits;

  fp = instance.fpt_set.fpt_64;
  fd = &instance.fixed;
  frac_bits = fd->frac_bits;

  fp = fp * (double)(0x1 << frac_bits);

  fixed_point_fp2fd_peform(fd->fixed_16, fp, 16, frac_bits);
  print_fixed_float_16(fd->fixed_16, frac_bits);
  fixed_point_fp2fd_peform(fd->fixed_32, fp, 32, frac_bits);
  print_fixed_float_32(fd->fixed_32, frac_bits);
  fixed_point_fp2fd_peform(fd->fixed_64, fp, 64, frac_bits);
  print_fixed_float_64(fd->fixed_64, frac_bits);
}

static inline void
fixed_point_fp2fd_peform(void *result, double fp, unsigned width, unsigned frac_bits)
{
  unsigned long long *tmp;
  unsigned sign;

  tmp = (unsigned long long *)&fp;
  /* input float point will be double only for fpt_set use double only */
  sign = GET_BIT(*tmp, 63);
  tmp = result;

  if (!is_fp2fd_overflow(fp, width, frac_bits))
    *tmp = (unsigned long long)fp;
  else
    *tmp = (~0ull >> 1) >> (64 - width);

  *tmp &= (~0ull >> (64 - width));

  fixed_point_set_sign(tmp, width, sign);
}

static inline void
fixed_point_set_sign(unsigned long long *fd, unsigned width, unsigned sign)
{
  if (fd)
    *fd |= (sign << (width - 1));
}

static signed
is_fp2fd_overflow(double fp, unsigned width, unsigned frac_bits)
{
  unsigned long long fd_max;

  fd_max = ~0ull >> 1;                         /* shift out the signature bit */
  fp = fp > 0 ? fp : - fp;
  if (16 == width || 32 == width || 64 == width)
  {
    fd_max >>= (64 - width);
    fd_max >>= frac_bits;
  }
  else
    return 0;

  if (fp > (double)fd_max)
  {
    printf("[34mWARNING[0m:Fp 2 Fd Overflow Occurs, Raw %f, Width %u, Frac %u\n",
      fp, width, frac_bits);
    return 1;
  }

  return 0;
}

