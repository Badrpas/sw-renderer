#include "defines.h"

Tec* _temp;
#define swap_t(a, b) _temp = a; a=b; b = _temp;


void triangle_v(Vec* v0, Vec* v1, Vec* v2, UINT32 color) {
  triangle_t(
      vec_to_tec(v0),
      vec_to_tec(v1),
      vec_to_tec(v2),
      color
  );
}


void triangle_t(Tec* t0, Tec* t1, Tec* t2, UINT32 color) {
  {
    Tec* t[3] = { t0, t1, t2 };
    for (int i = 0; i < 3; ++i) {
      line(
          t[i]->x,
          t[i]->y,
          t[(i + 1) % 3]->x,
          t[(i + 1) % 3]->y,
          0xFFFF00
      );
    }
  }
  if (t0->y > t1->y) { swap_t(t0, t1); }
  if (t0->y > t2->y) { swap_t(t0, t2); }
  if (t1->y > t2->y) { swap_t(t1, t2); }
  double total_height = t2->y - t0->y;

  for (UINT32 y = t0->y; y < t1->y; ++y) {
    int segment_height = (SINT32)t1->y - (SINT32)t0->y + 1;
    double alpha = (double)(y - t0->y) / total_height;
    double beta  = (double)(y - t0->y) / segment_height; // be careful with divisions by zero

    Tec a = { t0->x + (t2->x - t0->x) * alpha, t0->y + (t2->y - t0->y) * alpha };
    Tec b = { t0->x + (t1->x - t0->x) * beta , t0->y + (t1->y - t0->y) * beta };

    line(a.x, a.y, b.x, b.y, 0xFFFFFF);
    setPixel(a.x, y, 0xFF0000);
    setPixel(b.x, y, 0x00FF00);
  }
}

#undef swap_t