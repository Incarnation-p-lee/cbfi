#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

enum operation {
  FP2INT = 11,
  INT2FP,
};

enum encoding {
  IEEE754 = 0,
};

enum fpt_width {
  FLOAT_WIDTH_ALL,
  FLOAT_WIDTH_SINGLE = 32,
  FLOAT_WIDTH_DOUBLE = 64,
};

struct ieee754_float_32 {
  unsigned sign:1;
  unsigned exp:8;
  unsigned fraction:23;
};

struct ieee754_float_64 {
  unsigned      sign:1;
  unsigned      exp:11;
  unsigned long fraction:52;
};

struct float_point {
  float  fpt_32;
  double fpt_64;
};

struct convert {
  enum encoding             type;
  enum operation            opt;
  enum fpt_width            bwidth;
  unsigned char             raw[16];
  unsigned                  detail;
  struct float_point        fpt_set;
  void                      *data;
  union {
    struct ieee754_float_32 *fpt_32;
    struct ieee754_float_64 *fpt_64;
  }                         unpack;
};

#endif
