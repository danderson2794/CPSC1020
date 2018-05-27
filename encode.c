#include "encode.h"

/*
    Even though we will not have comments in our PPM file, I wrote this
    algorithm to be portable. Meaning it can be used with any PPM header,
    regardless of format. In my research, there were mainly 3 different header
    formats - formats meaning the order of P6, #, Height, Width, Max. This
    algorithm will catch for each variation.
*/


void readHeader(FILE * ppmImage, struct ppmHeader * ppmPtr)
{

    int i = 0, j = 0, k = 0;
    char header[100], width[5], height[5];

    fgets(header, 100, ppmImage);


/*
    For this program, I will hard code "P6" into the final encoded ppm file.
    If the first string is only 3 chars, I know there is only the P6 (meaning
    there is no comment on the first line). If it's P6 on one line only, I tell
    the compiler to continue reading. If the header does not equal "P6",
    I set i = 3, which will be used to find and skip comments.
*/

    if(strlen(header) == 3)
    {
        fgets(header, 100, ppmImage);
    }
    else
    {
        i = 3;
    }

/*
    This while-loop looks for multiple line comments and skips over them. In
    several ppm files I downloaded from Google, they had numerous line comments.
    Once again, I know ours will not, but this is for my to practice my skills
    and ensure portability.
*/

    while (header[0] == '#')
    {
        fgets(header, 100, ppmImage);
    }


    while (header[i] != ' ')
    {
        width[j] = header[i];
        i++, j++;
    }

    while (header[i] != ' ')
    {
        height[k] = header[i];
        i++, k++;
    }

    sscanf(width, "%d", &ppmPtr->col);
    sscanf(height, "%d", &ppmPtr->row);
    
        

}
