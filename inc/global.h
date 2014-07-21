#ifndef GLOBAL_H
#define GLOBAL_H


#define HIGH_32_BITS(x)         ((x) >> 32)
#define LOW_32_BITS(x)         ((x) & UINT_MAX)
#define LONG_SIZE              sizeof(long)

struct convert instance;

#endif
