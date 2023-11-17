#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include <string.h>
image* loadImageFromFile(char* filename){
    //Loads a bmp image from a gicen filepath and then converts it to grayscale and returns it as an image struct
    FILE* file = fopen(filename, "rb");
    if(file == NULL){
        printf("Error in opening input file");
        return NULL;
    }
    int length = strlen(filename);
    char* extension = filename + length - 3;
    if(strcmp(extension, "bmp") != 0){
        printf("Error: file must be a bmp");
        return NULL;
    }
    image* img = malloc(sizeof(image));
    img->header = malloc(sizeof(unsigned char)*54);
    int i;
    for(i=0;i<54;i++)
    {
        img->header[i] = getc(file);
    }
    img->height = *(int*)&(img->header)[18];
    img->width = *(int*)&(img->header)[22];
   
	int size = img->height*img->width;

    img->data = malloc(sizeof(unsigned char)*size);

	unsigned char buffer[size][3];
    for(i=0;i<size;i++)											
	{
		
		buffer[i][2]=getc(file);								
		buffer[i][1]=getc(file);									
		buffer[i][0]=getc(file);									
			
		img->data[i] = (buffer[i][0]*0.3) + (buffer[i][1]*0.59)	+ (buffer[i][2]*0.11);
	}
    return img;
}

int outputImageToFile(image* img, char* filename){
    //Outputs an image struct to a bmp file returns 1 if successful and 0 if not
    FILE* file = fopen(filename, "wb");
    if(file == NULL){
        printf("Error in opening output file");
        return 0;
    }
    
    fwrite(img->header,sizeof(unsigned char),54,file);
    int size = img->height*img->width;

        int i;
    for(i=0;i<size;i++){
        putc(img->data[i],file);
        putc(img->data[i],file);
        putc(img->data[i],file);
    }
    fclose(file);
    return 1;
}