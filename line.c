#include "defines.h"
#include <stdlib.h>


void line(UINT32 x0, UINT32 y0, UINT32 x1, UINT32 y1, UINT32 color) {
  UINT32 xs = x0;
  UINT32 ys = y0;
  UINT32 xl = x1;
  UINT32 yl = y1;

  UINT32 steep = 0;
  UINT32 xlength = abs((int)xl - (int)xs);
  UINT32 ylength = abs((int)yl - (int)ys);

  if (xlength < ylength) { // if the line is steep, we transpose the image
    xs = y0;
    ys = x0;
    xl = y1;
    yl = x1;
    steep = 1;
  }

  if (xs>xl) { // make it left−to−right
    UINT32 t = xs;
    xs = xl;
    xl = t;
    t = ys;
    ys = yl;
    yl = t;
  }
  for (int x=xs; x<=xl; x++) {
    float t = (x-xs)/(float)(xl-xs);
    int y = ys*(1.-t) + yl*t;
    if (steep) {
      setPixel(y, x, color);
    } else {
      setPixel(x, y, color);
    }
  }
  return;

  // =======

  if (xlength < ylength) {
    xs = y0;
    ys = x0;
    xl = y1;
    ys = x1;
    steep = 1;
  }

  if (xs > xl) {
    xs = x1;
    ys = y1;
    xl = x0;
    yl = y0;
  }

  float xlengthf = (float)xl - (float)xs;
  float ylengthf = (float)yl - (float)ys;
  for (UINT32 x = xs; x < xl; ++x) {
    UINT32 y = ys + ylengthf * ((float)(x - xs) / xlengthf);

    if (steep) {
      setPixel(y, x, color);
    } else {
      setPixel(x, y, color);
    }
  }

}