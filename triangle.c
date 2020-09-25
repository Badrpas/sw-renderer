#include "defines.h"

void triangle(Vec* v1, Vec* v2, Vec* v3, UINT32 color) {
  Vec* v[3] = { v1, v2, v3 };

  for (int i = 0; i < 3; ++i) {
    line(
        to_screen_x(v[i]->x),
        to_screen_y(-v[i]->y),
        to_screen_x(v[(i + 1) % 3]->x),
        to_screen_y(-v[(i + 1) % 3]->y),
        color
    );
  }
}
