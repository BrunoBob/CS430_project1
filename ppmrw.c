#include "ppmrw.h"

int main(int argc, char *argv[]){
  if(argc < 4){
    fprintf(stderr, "Error : Convention is -> ppmrw type_of_conversion input.ppm ouput.ppm\n");
  }
  return 0;
}
