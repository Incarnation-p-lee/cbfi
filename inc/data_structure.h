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
  FLOAT_WIDTH_HALF   = 16,
  FLOAT_WIDTH_SINGLE = 32,
  FLOAT_WIDTH_DOUBLE = 64,
};

struct ieee754_float_16 {
  unsigned fraction:10;
  unsigned exp:5;
  unsigned sign:1;
};

struct ieee754_float_32 {
  unsigned fraction:23;
  unsigned exp:8;
  unsigned sign:1;
};

struct ieee754_float_64 {
  unsigned long fraction:52;
  unsigned      exp:11;
  unsigned      sign:1;
};

struct float_point {
  float  fpt_16;
  float  fpt_32;
  double fpt_64;
};

struct convert {
  enum encoding             type;
  enum operation            opt;
  enum fpt_width            bwidth;
  unsigned                  detail;
  unsigned char             raw[16];
  struct float_point        fpt_set;
  void                      *data;
  /*
    data point to the real data we get.
    If fp 2 int, data = raw,
    If int 2 fp, data = &fpt_set
  */
};

#endif
