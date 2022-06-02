#include "defines.h"


#define POOL_CAPACITY 1024
Tec pool[POOL_CAPACITY];
UINT32 pool_pos = 0;

Tec* vec_to_tec(Vec* v) {
  if (pool_pos + 1 == POOL_CAPACITY) {
    pool_pos = 0;
    printf("Pool capacity reset\n");
  }
  Tec* tec = &(pool[pool_pos++]);
  tec->x = to_screen_x(v->x);
  tec->y = to_screen_y(v->y);
  return tec;
}
