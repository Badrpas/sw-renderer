#include "defines.h"
#include <math.h>

BYTE rawData[PIXEL_COUNT * PIXEL_SIZE];

BYTE header[HEADER_SIZE];

void init_tga_header();

double* get_vertex(struct obj* obj, UINT32 idx) {
  return obj->vertices + ((idx - 1) * 3);
}

Vec* get_vec(struct obj* obj, UINT32 idx) {
  return (Vec*)get_vertex(obj, idx);
}

UINT32 to_screen_x(double x) {
  return HALF_WIDTH + (SINT32) ((x) * (double) HALF_WIDTH);
}

UINT32 to_screen_y(double y) {
  return HALF_HEIGHT + (SINT32) ((y) * (double) HALF_HEIGHT);
}

#define Xidx 0
#define Yidx 1
#define Zidx 2

#define PI 3.14159265359

int main() {
  FILE* file = fopen("../viewer/public/out.tga", "wb");
  init_tga_header();
  fwrite(header, 1, HEADER_SIZE, file);

  for (int i = 0; i < PIXEL_COUNT * PIXEL_SIZE; ++i) {
    rawData[i] = 0;
  }

  struct obj* obj = read_obj("../obj/head.obj");
  printf("\n\n\n========\n\n\n");
  printf("Vertices count: %u\nFace count: %u\n", obj->vertex_count, obj->face_count);

  UINT8 kek = 12;

  for (int k = 1; k <= kek; ++k) {
    double* v = get_vertex(obj, k);
    if (kek--) printf("%f, %f, %f\n", v[Xidx], v[Yidx], v[Zidx]);
  }

  for (int j = 0; j < obj->face_count; ++j) {
    UINT32 face_idx = j * 3 * 3;

    UINT16 idx1 = obj->faces[face_idx + 0];
    UINT16 idx2 = obj->faces[face_idx + 3];
    UINT16 idx3 = obj->faces[face_idx + 6];

    triangle_v(
        get_vec(obj, idx1),
        get_vec(obj, idx2),
        get_vec(obj, idx3),
        0x00FFFF
    );
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
