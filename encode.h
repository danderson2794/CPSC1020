/*
________________________________________________________________________________
    
    Damion Anderson
    CPSC1020 Sm2018
    daander@clemson.edu
________________________________________________________________________________
*/

#ifndef ENCODE_H
#define ENCODE_H
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*---------------------   Structures  ----------------------------------------*/
struct header_t{
    int col;
    int row;
    int maxColor;
};

struct pixel_t{
    unsigned char r;
    unsigned char g; 
    unsigned char b;
};

     
/*---------------------   Prototypes  ----------------------------------------*/

void readHeader(FILE * ppmImage, struct header_t * ppmHeader);
struct pixel_t ** readPixel(FILE *ppmImage, struct header_t *ppmHeader);
void writeHeader(struct header_t * ppmHeader);
void writePixels(struct pixel_t ** arr, struct header_t * ppmPtr, int col, 
    int arrInt[][col]);
void removeDigit(struct pixel_t** arr, struct header_t* ppmPtr);
void dec2bin (int col, int row, int arrPtr[row][col], int var[row]);
void encodeMsg(FILE * ppmImage, struct header_t * ppmPtr, struct pixel_t ** 
    pixelPtr, char *);




#endif
