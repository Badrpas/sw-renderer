#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

void* space[1024 * 1024 * 128];
UINT32 space_pos = 0;

#define MODE_V 1
#define MODE_F 2
#define MODE_UNKNOWN 0xFF

char isDelimeter(char c, char* delimiters) {
  UINT8 p = 0;
  while (delimiters[p] != '\0') {
    if (delimiters[p] == c) return 1;
    p++;
  }
  return 0;
}
char num_buf[32];
UINT8 num_buf_pos = 0;
char* handle_word(char c, char* delimeters) {
  if (isDelimeter(c, delimeters)) {
    num_buf[num_buf_pos] = '\0';
    num_buf_pos = 0;
    return num_buf;
  }
  num_buf[num_buf_pos++] = c;
  return 0;
}

UINT8 qwe = 9;

UINT32 vertex_count = 0;
void vertex_handler(char cc) {
  char* word = handle_word(cc, " \n");
  if (word) {
    double d = atof(word);
    ((double*) ((UINT8*) space + space_pos))[0] = d;
    if (qwe) {
      printf("%f:\n", d);
      UINT8* dc = &d;
      printf("%X %X %X %X\n", dc[0], dc[1], dc[2], dc[3]);
      dc = (UINT8*) space + space_pos;
      printf("%X %X %X %X\n\n", dc[0], dc[1], dc[2], dc[3]);
      qwe--;
    }
    space_pos += sizeof(d);
  }
  if (cc == '\n') vertex_count++;
}
UINT16* faces = 0;
UINT32 face_count = 0;

void face_handler(char cc) {
  if (!faces) {
    faces = (UINT16*) ((char*) space + space_pos);
  }
  char* word = handle_word(cc, " /\n");
  if (word) {
    UINT16 d = atoi(word);
    ((UINT16*) ((UINT8*) space + space_pos))[0] = d;
    space_pos += sizeof(d);
  }
  if (cc == '\n') {
    face_count++;
  }
}

struct obj* read_obj(char* filename) {
  FILE* file;
  file = fopen(filename, "r");
  if (!file) return 0;

  int c;
  char cc;
  UINT8 mode = 0;
  while ((c = getc(file)) != EOF) {
    cc = (char)c;
    if (!mode) {
      switch (cc) {
        case 'v': {
          if ((char)getc(file) == ' ') {
            mode = MODE_V;
          } else {
            mode = MODE_UNKNOWN;
          } break;
        }
        case 'f': {
          if (((char)(c = getc(file))) == ' ') {
            mode = MODE_F; break;
          } else {
            mode = MODE_UNKNOWN;
          } break;
        }
        default: mode = MODE_UNKNOWN;
      }
      continue;
    }

    if (mode == MODE_V) {
      vertex_handler(cc);
    } else if (mode == MODE_F) {
      face_handler(cc);
    }

    if (cc == '\n') {
      mode = 0;
    }
  }

  // TODO: Swap with data from space
  struct obj* obj = malloc(sizeof(struct obj));
  obj->vertices = (double*)space;
  obj->vertex_count = vertex_count;
  obj->faces = faces;
  obj->face_count = face_count;
  return obj;
}
