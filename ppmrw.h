#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char* name;
  FILE* file;
  char type;
  int width, height;
} *ppmImage;


char getConversionType(char* arg);
ppmImage openImage(ppmImage image, char* name);
void closeImage(ppmImage image);
