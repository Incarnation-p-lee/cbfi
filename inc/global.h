#ifndef GLOBAL_H
#define GLOBAL_H


#define HIGH_32_BITS(x)         ((x) >> 32)
#define LOW_32_BITS(x)         ((x) & UINT_MAX)
#define LONG_SIZE              sizeof(long)
#define FPT_16_BIAS            15
#define FPT_32_BIAS            31
#define HIGH_BITS_MASK(n)      ((~0x0ull >> (n)) << (n))
#define LOW_BITS_MASK(n)       ((0x1ull << ((n) + 1)) - 1)
#define GET_BIT(op, n)         (((op) >> (n)) & 0x1ull)
#define SET_BIT(op, n)         ((op) | (0x1ull << (n)))
#define CLR_BIT(op, n)         ((op) & ((~0x0ull) ^ (0x1ull << (n))))
#define GET_BITS(op, b1, b2)   (((op) >> (b1)) & ((0x2ull << ((b2) - (b1))) - 1))

struct convert instance;

#endif
