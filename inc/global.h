#ifndef GLOBAL_H
#define GLOBAL_H


#define DETAIL_ENABLED         1
#define DETAIL_DISABLED        0
#define HIGH_32_BITS(x)         ((x) >> 32)
#define LOW_32_BITS(x)         ((x) & UINT_MAX)
#define LONG_SIZE              sizeof(long)
#define FPT_16_BIAS            15
#define FPT_32_BIAS            31
#define HIGH_BITS_MASK(n)      ((~0x0 >> n) << n)
#define LOW_BITS_MASK(n)       ((0x1 << (n) + 1) - 1)
#define GET_BIT(op, n)         (((op) >> n) & 0x1)
#define SET_BIT(op, n)         ((op) | (0x1 << n))
#define CLR_BIT(op, n)         ((op) & ((~0x0) ^ (0x1 << n)))
#define GET_BITS(op, b1, b2)   (((HIGH_BITS_MASK(b1) & LOW_BITS_MASK(b2)) & \
                                 (op)) >> b1)

struct convert instance;

#endif
