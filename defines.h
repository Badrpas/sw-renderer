
#ifndef RENDER_MY_WAY_DEFINES_H
#define RENDER_MY_WAY_DEFINES_H


#define BYTE unsigned char
#define UINT8 unsigned char
#define UINT16 unsigned short
#define SINT16 short
#define UINT32 unsigned int
#define SINT32 int

#define WIDTH 800
#define HEIGHT 600
#define HALF_WIDTH WIDTH / 2
#define HALF_HEIGHT HEIGHT / 2
#define PIXEL_COUNT WIDTH * HEIGHT
#define PIXEL_SIZE 3

#define HEADER_SIZE 18


void setPixel(UINT32, UINT32, UINT32);
void line(UINT32, UINT32, UINT32, UINT32, UINT32);

struct obj;

struct obj {
  double* vertices;
  UINT32 vertex_count;
  UINT16* faces;
  UINT32 face_count;
};

struct obj* read_obj(char*);

#endif //RENDER_MY_WAY_DEFINES_H
