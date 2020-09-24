#include "defines.h"
#include <stdlib.h>


void line(UINT x0, UINT y0, UINT x1, UINT y1, UINT color) {
  UINT xs = x0;
  UINT ys = y0;
  UINT xl = x1;
  UINT yl = y1;

  UINT xlength = abs((int)xl - (int)xs);
  UINT ylength = abs((int)yl - (int)ys);

  if (xlength > ylength) {
    if (x0 > x1) {
      xs = x1;
      ys = y1;
      xl = x0;
      yl = y0;
    }
    for (UINT x = xs; x < xl; ++x) {
      UINT y = ys + ylength * ((float)(x - xs) / xlength);
      setPixel(x, y, color);
    }
  } else {
    if (y0 > y1) {
      xs = x1;
      ys = y1;
      xl = x0;
      yl = y0;
    }
    for (UINT y = ys; y != yl; y++) {
      UINT x = xs + xlength * ((float)(y - ys) / ylength);
      setPixel(x, y, color);
    }
  }

}