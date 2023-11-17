#include <stdio.h>
#include "matrix.h"
#include "image.h"
#define FILEINPUT "/Users/spencerevans-cole/Desktop/Coding/SVD-Image-Compression/images/meAndAbby/meAndAbby.bmp"
#define FILEOUTPUT "/Users/spencerevans-cole/Desktop/Coding/SVD-Image-Compression/images/meAndAbby/meAndAbbyGray.bmp"
int main(int argc, char *argv[]) {
   image* img = loadImageFromFile(FILEINPUT);
   int i = outputImageToFile(img, FILEOUTPUT);
   return 0;
}