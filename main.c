#include <stdio.h>
#include "matrix.h"
#define FILEINPUT "/Users/spencerevans-cole/Desktop/Coding/SVD-Image-Compression/images/meAndAbby/meAndAbby.bmp"
#define FILEOUTPUT "/Users/spencerevans-cole/Desktop/Coding/SVD-Image-Compression/images/meAndAbby/meAndAbbyGray.bmp"
int main(int argc, char *argv[]) {
    FILE* fIn = fopen(FILEINPUT, "rb"); 
    FILE* fOut = fopen(FILEOUTPUT, "wb");
	if(fIn == NULL){
		printf("Error in opening input file");
		return -1;
	}
	if(fOut == NULL){
		printf("Error in opening output file");
		return -1;
	}
    int i,y = 0;
    unsigned char byte[54];
    for(i=0;i<54;i++)											
	{									
		byte[i] = getc(fIn);								
	}

	fwrite(byte,sizeof(unsigned char),54,fOut);	
    int height = *(int*)&byte[18];
	int width = *(int*)&byte[22];
	int bitDepth = *(int*)&byte[28];
    printf("width: %d\n",width);
	printf("height: %d\n",height );

	int size = height*width;

	unsigned char buffer[size][3];	
    for(i=0;i<size;i++)											//RGB to gray
	{
		y=0;
		buffer[i][2]=getc(fIn);									//blue
		buffer[i][1]=getc(fIn);									//green
		buffer[i][0]=getc(fIn);									//red
			
		y=(buffer[i][0]*0.3) + (buffer[i][1]*0.59)	+ (buffer[i][2]*0.11);			//conversion formula of rgb to gray

		putc(y,fOut);
		putc(y,fOut);
		putc(y,fOut);
	}
	
	fclose(fOut);
	fclose(fIn);
    return 0;
}