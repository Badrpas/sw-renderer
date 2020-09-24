
#ifndef RENDER_MY_WAY_DEFINES_H
#define RENDER_MY_WAY_DEFINES_H


#define BYTE unsigned char
#define UINT unsigned int

#define WIDTH 800
#define HEIGHT 600
#define PIXEL_COUNT WIDTH * HEIGHT
#define PIXEL_SIZE 3

#define HEADER_SIZE 18


void setPixel(UINT, UINT, UINT);
void line(UINT, UINT, UINT, UINT, UINT);

#endif //RENDER_MY_WAY_DEFINES_H
