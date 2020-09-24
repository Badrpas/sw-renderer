#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

void* space[1024 * 1024 * 128];
unsigned int space_pos = 0;

#define MODE_V 1
#define MODE_F 2
#define MODE_UNKNOWN 0xFF

char num_buf[32];
UINT8 num_buf_pos = 0;
char* handle_word(char c) {
  if (c == ' ' || c == '\n') {
    num_buf[num_buf_pos] = '\0';
    num_buf_pos = 0;
    return num_buf;
  }
  num_buf[num_buf_pos++] = c;
  return 0;
}

unsigned int vertex_count = 0;
void vertex_handler(char cc) {
  char* word = handle_word(cc);
  if (word) {
    float f = (float)atof(word);
    ((float*)space)[space_pos] = f;
    UINT8* sc = space + space_pos;
//    printf("%d %d %d %d %d\n", space_pos, sc[0], sc[1], sc[2], sc[3]);
    space_pos += sizeof(f);
  }
  if (cc == '\n') vertex_count++;
}

struct obj* read_obj(char* filename) {
  FILE* file;
  file = fopen(filename, "r");
  if (!file) return 0;

  UINT8 skip = 0;
  int c;
  char cc;
  UINT8 mode = 0;
  while ((c = getc(file)) != EOF) {
    if (skip) {
      skip = 0;
      continue;
    }
    cc = (char)c;
    if (!mode) {
      switch (cc) {
        case 'v': mode = MODE_V; break;
        case 'f': mode = MODE_F; break;
        default: mode = MODE_UNKNOWN;
      }
      skip = 1;
      continue;
    }

    if (mode == MODE_V) {
      vertex_handler(cc);
    }

    if (cc == '\n') {
      mode = 0;
    }
  }

  // TODO: Swap with data from space
  struct obj* obj = malloc(sizeof(struct obj));
  obj->vertices = (float*)space;
  obj->vertex_count = vertex_count;
  return obj;
}
