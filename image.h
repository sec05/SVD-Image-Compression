typedef struct
{
    int width;
    int height;
    unsigned char *header;
    unsigned char *data;
} image;

image* loadImageFromFile(char* filename);
int outputImageToFile(image* img, char* filename);