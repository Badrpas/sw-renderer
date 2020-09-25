#include "defines.h"

void triangle(Vec* v1, Vec* v2, Vec* v3, UINT32 color) {


  line(
      to_screen_x(v1->x),
      to_screen_y(-v1->y),
      to_screen_x(v2->x),
      to_screen_y(-v2->y),
      color
  );
  line(
      to_screen_x(v2->x),
      to_screen_y(-v2->y),
      to_screen_x(v3->x),
      to_screen_y(-v3->y),
      color
  );
  line(
      to_screen_x(v3->x),
      to_screen_y(-v3->y),
      to_screen_x(v1->x),
      to_screen_y(-v1->y),
      color
  );
}
