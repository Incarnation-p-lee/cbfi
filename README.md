cbfi
gcc required, just make.

============

conversion between float point and its' binary layout
   This tiny tool _DO_ _NOT_ guarantee the correct result for rounding. It
main focus on the binary layout in memory or internal structure of one float point.
```
Format:
   cbfi 0xXXXXXXXX
       Means convert binary layout to float point, only 16, 32, 64 bits is valid.
   cbfi XXXXX.XX
       Means convert to binary layout of float point
   Also, you can use -d option to show more information you may need.
```

Sample:

```
<22>pli[9903]@~/Workspace/project/cbfi*1 > cbfi 1.0
half float point[16]:        0X3C00
single float point[32]:      0X3F800000
double float point[64]:      0X3FF0000000000000

<24>pli[9904]@~/Workspace/project/cbfi*1 > cbfi 1.0 -d
half float point[16]:        0X3C00
            Hexadecimal      Decimal          Binary
  |sign:    0000000000000000 0000000000000000 0B
  |exp :    000000000000000f 0000000000000015 01111B
  |frac:    0000000000000000 0000000000000000 0000000000B

single float point[32]:      0X3F800000
            Hexadecimal      Decimal          Binary
  |sign:    0000000000000000 0000000000000000 0B
  |exp :    000000000000007f 0000000000000127 01111111B
  |frac:    0000000000000000 0000000000000000 00000000000000000000000B

double float point[64]:      0X3FF0000000000000
            Hexadecimal      Decimal          Binary
  |sign:    0000000000000000 0000000000000000 0B
  |exp :    00000000000003ff 0000000000001023 01111111111B
  |frac:    0000000000000000 0000000000000000 0000000000000000000000000000000000000000000000000000B

<26>pli[9905]@~/Workspace/project/cbfi*1 > cbfi 0x7c00
half float point[16]:        inf
<27>pli[9906]@~/Workspace/project/cbfi*1 > cbfi 0x7c00 -d
half float point[16]:        inf
            Hexadecimal      Decimal          Binary
  |sign:    0000000000000000 0000000000000000 0B
  |exp :    000000000000001f 0000000000000031 11111B
  |frac:    0000000000000000 0000000000000000 0000000000B

<40>pli[9901]@~/Workspace/project/cbfi*1 > cbfi 0x47dc0024
single float point[32]:      112640.2812500000000000
<41>pli[9902]@~/Workspace/project/cbfi*1 > cbfi 0x47dc0024 -d
single float point[32]:      112640.2812500000000000
            Hexadecimal      Decimal          Binary
  |sign:    0000000000000000 0000000000000000 0B
  |exp :    000000000000008f 0000000000000143 10001111B
  |frac:    00000000005c0024 0000000006029348 10111000000000000100100B
```
