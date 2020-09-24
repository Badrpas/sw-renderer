
#ifndef RENDER_MY_WAY_DEFINES_H
#define RENDER_MY_WAY_DEFINES_H


#define BYTE unsigned char
#define UINT8 unsigned char
#define UINT32 unsigned int

#define WIDTH 800
#define HEIGHT 600
#define PIXEL_COUNT WIDTH * HEIGHT
#define PIXEL_SIZE 3

#define HEADER_SIZE 18


void setPixel(UINT32, UINT32, UINT32);
void line(UINT32, UINT32, UINT32, UINT32, UINT32);

struct obj;

struct obj {
  float* vertices;
  unsigned int vertex_count;
};

struct obj* read_obj(char*);

#endif //RENDER_MY_WAY_DEFINES_H
