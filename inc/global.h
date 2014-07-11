#ifndef GLOBAL_H
#define GLOBAL_H


#define DETAIL_ENABLED         1
#define DETAIL_DISABLED        0
#define HIGH_32_BITS(x)         ((x) >> 32)
#define LOW_32_BITS(x)         ((x) & UINT_MAX)
#define LONG_SIZE              sizeof(long)

struct convert instance;

#endif
