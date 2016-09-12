#include "ppmrw.h"

/*
* RETURN
*
* 0 = DONE
* 1 = Wrong number of arg
* 2 = Wrong type of conversion
* 3 = Error opening file : file dont exist
* 4 = Format not ppm P3 or ppm P6
*/

int main(int argc, char *argv[]){
  char conversionType;  // 0 = convert to P6 | 1 = convert to P3

  ppmImage inputImage = NULL;
  ppmImage outputImage = NULL;

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

  //Open input file
  inputImage = openImage(inputImage,argv[2]);
  if(inputImage == NULL){
    fprintf(stderr, "Error : Cannot open file %s\n", argv[2]);
    return 3;
  }
  if((inputImage->type != 3) && (inputImage->type != 6)){
    fprintf(stderr, "Error : Wrong input file format, expect ppm file in format P3 or P6 \n");
    return 4;
  }

  //Close input and output files
  closeImage(inputImage);

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

ppmImage openImage(ppmImage image, char* name){
    image = (ppmImage) malloc(sizeof(*image));
    image->name = name;
    image->type = 0;

    //Opening file
    image->file = fopen(name, "r");
    if(image->file == NULL){
      free(image);
      return NULL;
    }

    //Checking file format
    char* buffer = (char*)malloc(2*sizeof(char));
    fread(buffer, sizeof(char), 2, image->file);
    if(!strcmp(buffer, "P3")){
      image->type = 3;
    }
    else if(!strcmp(buffer, "P6")){
      image->type = 6;
    }
    return image;
}

void closeImage(ppmImage image){
  if(image->file != NULL){
    fclose(image->file);
  }
  free(image);
}
