#include <stdio.h>
#include "defines.h"


BYTE rawData[PIXEL_COUNT * PIXEL_SIZE];

BYTE header[HEADER_SIZE];

void init_tga_header();

int main() {
  FILE* file = fopen("../viewer/public/out.tga", "wb");
  init_tga_header();
  fwrite(header, 1, HEADER_SIZE, file);

  for (int i = 0; i < PIXEL_COUNT * PIXEL_SIZE; ++i) {
    rawData[i] = 255;
  }

  line(1, 1, 500, 500, 0x0000FF);
  line(500, 1, 500, 500, 0x00FF00);
  line(500, 1, 1, 500, 0xFF0000);

  struct obj* obj = read_obj("../obj/head.obj");
  printf("\n\n\n========\n\n\n");
  float m = 10000.0f;
  for (int j = 0; j < obj->vertex_count; ++j) {
    UINT32 pos = j * 3;

    unsigned int x = (UINT32) (obj->vertices[pos + 1] * m);
    unsigned int y = (UINT32) (obj->vertices[pos + 2] * m);

//    printf("%d %d %f %f\n", x, y, obj->vertices[pos], obj->vertices[pos+1]);

    setPixel(x, y, 0xFF0000);
  }

  fwrite(rawData, PIXEL_SIZE, PIXEL_COUNT, file);

  fclose(file);
  printf("Done.\n");
  return 0;
}

void setPixel(UINT32 x, UINT32 y, UINT32 color) {
  if (x > WIDTH || y > HEIGHT) return;
  rawData[x * PIXEL_SIZE + 0 + y * WIDTH * PIXEL_SIZE] = 0xFF & (color);
  rawData[x * PIXEL_SIZE + 1 + y * WIDTH * PIXEL_SIZE] = 0xFF & (color >> 8);
  rawData[x * PIXEL_SIZE + 2 + y * WIDTH * PIXEL_SIZE] = 0xFF & (color >> 16);
}

void init_tga_header() {
  header[0] = 0;
  header[1] = 0;
  header[2] = 2;
  header[12] = 255 & WIDTH;
  header[13] = 255 & (WIDTH >> 8);
  header[14] = 255 & HEIGHT;
  header[15] = 255 & (HEIGHT >> 8);
  header[16] = 24;
  header[17] = 32;
}
