/*
________________________________________________________________________________
    
    Damion Anderson
    CPSC1020 Sm2018
    daander@clemson.edu
________________________________________________________________________________
*/

#include "encode.h"

int main(int argc, char * argv[])
{
//The best of messages to encode - my favorite 80's song, ha! 
    char message[] = "8675309"; 
/*
    This if statement catches for an incorrect input. This program needs a ppm
    file input from the command line - else it will not run.
*/

    if (argc == 1)
    {
        fprintf(stderr, "<executable> <image_name>\n");
        exit(1);
    }

    FILE * ppmImage;
    ppmImage = fopen(argv[1], "r");


/*
    If there's an error opening the image, this if statment will catch it and
    cancel it.
*/

    if (ppmImage == NULL)
    {
        fprintf(stderr,"File open error. Exiting Program");
        exit(1);
    }

    struct header_t header;
    struct header_t *ppmPtr = &header;
    
    readHeader(ppmImage, ppmPtr);

    struct pixel_t ** pixelPtr = readPixel(ppmImage, ppmPtr);
    
    encodeMsg(ppmImage, ppmPtr, pixelPtr, message);


    return 0;
}
