#include "encode.h"

int main(int argc, char * argv[])
{

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

struct ppmHeader header;

struct ppmHeader *ppmPtr = &header;

readHeader(ppmImage, ppmPtr);

printf("ppmHeader.col = %d\n", ppmPtr->col);
printf("ppmHeader.row is = %d\n", ppmPtr->row);




    return 0;
}
