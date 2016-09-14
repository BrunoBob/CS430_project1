#include "ppmrw.h"

/*
* RETURN
*
* 0 = DONE
* 1 = Wrong number of arg
* 2 = Wrong type of conversion
* 3 = Error opening file : file dont exist
* 4 = Format not ppm P3 or ppm P6
* 5 = File corrupted : Can't read image size
*/

int main(int argc, char *argv[]){
  char conversionType;  // 3 = convert to P3 | 6 = convert to P6

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
  inputImage = openImage(argv[2]);
  if(inputImage == NULL){
    fprintf(stderr, "Error : Cannot open file %s\n", argv[2]);
    return 3;
  }
  if((inputImage->type != 3) && (inputImage->type != 6)){
    fprintf(stderr, "Error : Wrong input file format, expect ppm file in format P3 or P6 \n");
    return 4;
  }
  if((inputImage->width == 0) || (inputImage->height == 0)){
    fprintf(stderr, "Error : Can't read image size \n");
    return 5;
  }

  //Convert image
  outputImage = convertImage(inputImage, argv[3], conversionType);

  //Close input and output files
  closeImage(inputImage);
  closeImage(outputImage);

  return 0;
}

char getConversionType(char* arg){
  if(!strcmp(arg, "3")){
    return 3;
  }
  else if(!strcmp(arg, "6")){
    return 6;
  }
  return -1;
}

ppmImage openImage(char* name){
  ppmImage image = (ppmImage) malloc(sizeof(*image));
  image->name = name;
  image->type = 0;
  image->width = image->height = 0;

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
  free(buffer);
  if(image->type == 0){
    return image;
  }

  //Reading comment
  buffer = (char*)malloc(sizeof(char));
  fread(buffer, sizeof(char), 1, image->file); //read end of line car
  fread(buffer, sizeof(char), 1, image->file); //Read first car to see if comment
  while((buffer != NULL) && (!strcmp(buffer, "#"))){
    while(strcmp(buffer, "\n")){
      fread(buffer, sizeof(char), 1, image->file);
    }
    fread(buffer, sizeof(char), 1, image->file);
  }

  //Get image size
  int numberSize = 1;
  char* number = (char*)malloc(sizeof(char)*numberSize);
  number[numberSize-1] = buffer[0];
  while((fread(buffer, sizeof(char), 1, image->file)) && (strcmp(buffer, " "))){
    if(buffer != NULL){
      numberSize++;
      realloc(number,sizeof(char)*numberSize);
      number[numberSize-1] = buffer[0];
    }
  }
  image->width = atoi(number);
  free(number);

  numberSize = 0;
  number = (char*)malloc(sizeof(char)*numberSize);
  while((fread(buffer, sizeof(char), 1, image->file)) && (strcmp(buffer, "\n"))){
    if(buffer != NULL){
      numberSize++;
      realloc(number,sizeof(char)*numberSize);
      number[numberSize-1] = buffer[0];
    }
  }
  image->height = atoi(number);
  free(number);

  //Reading max color value
  do{
    fread(buffer, sizeof(char), 1, image->file);
  }while(strcmp(buffer, "\n"));

  free(buffer);
  return image;
}

ppmImage convertImage(ppmImage inputImage, char* outputName, char conversionType){
  //init output image data
  ppmImage outputImage = (ppmImage) malloc(sizeof(*outputImage));
  outputImage->name = outputName;
  outputImage->type = conversionType;
  outputImage->width = inputImage->width;
  outputImage->height = inputImage->height;

  //opening output file
  outputImage->file = fopen(outputName, "w");
  if(outputImage->file == NULL){
    free(outputImage);
    return NULL;
  }

  //Write header
  fprintf(outputImage->file, "P%d\n#Wrtitten by PPMRW program made by Bruno TESSIER\n%d %d\n255\n", outputImage->type, outputImage->width, outputImage->height);


  unsigned char* buffer = NULL;
  if(inputImage->type == 3){
    buffer = (unsigned char*)malloc(4 * sizeof(char));
  }
  else{
    buffer = (unsigned char*)malloc(2 * sizeof(char));
  }
  int read = 1;
  do{
    //Read data
    if(inputImage->type == 3){
      buffer = fgets(buffer, 5, inputImage->file);
    }
    else{
      read = fread(buffer, sizeof(char), 1, inputImage->file);
    }

    //Write data
    if(buffer != NULL){
      if(conversionType == 3){
        //P3 to P3
        if(inputImage->type == 3){
          fprintf(outputImage->file, "%s",buffer);
        }
        //P6 to P3
        else{
          fprintf(outputImage->file, "%d\n", buffer[0]);
        }
      }
      else{
        //P3 to P6
        if(inputImage->type == 3){
          unsigned char *data = (char*)malloc(sizeof(char));
          data[0] = (unsigned char) atoi(buffer);
          fwrite(data, sizeof(char), 1, outputImage->file);
          free(data);
        }
        //P6 to P6
        else{
          fwrite(buffer, sizeof(char), 1, outputImage->file);
        }
      }
    }
  }while(buffer != NULL && read != 0);
  free(buffer);

  return outputImage;
}

void closeImage(ppmImage image){
  if(image->file != NULL){
    fclose(image->file);
  }
  free(image);
}
