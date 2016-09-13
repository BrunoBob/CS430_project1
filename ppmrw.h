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
ppmImage openImage(char* name);
ppmImage convertImage(ppmImage inputImage, char* outputName, char conversionType);
void closeImage(ppmImage image);
