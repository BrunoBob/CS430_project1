#include "ppmrw.h"

/*
* RETURN
*
* 0 = DONE
* 1 = Wrong number of arg
* 2 = Wrong type of conversion
*/

int main(int argc, char *argv[]){
  char conversionType;  // 0 = P3 to P6 | 1 = P6 to P3

  char *inputName;
  char *OutputName;

  FILE *InputFile;
  FILE *OutputFile;

  int width, height;

  //Verification of argument number
  if(argc < 4){
    fprintf(stderr, "Error : Convention is -> ppmrw type_of_conversion input.ppm ouput.ppm\n");
    return 1;
  }

  //Get conversion type
  if((conversionType = getConversionType(argv[1])) == -1){
    fprintf(stderr, "Error : Type of conversion must be  3 (convert to P3) or 6 (convert to P6)\n");
    return 2;
  }

  return 0;
}

char getConversionType(char* arg){
  if(!strcmp(arg, "3")){
    return 0;
  }
  else if(!strcmp(arg, "6")){
    return 1;
  }
  return -1;
}
