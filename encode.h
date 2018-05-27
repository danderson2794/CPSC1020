#ifndef ENCODE_H
#define ENCODE_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>


/*---------------------   Structures  ----------------------------------------*/
    /*typedef struct Header{
        int col, row;
    } header_t;
    */

    struct ppmHeader{
        int col;
        int row;
    };

    struct pixel{
        unsigned char r, g, b;
    };

     
/*---------------------   Prototypes  ----------------------------------------*/

    void readHeader(FILE * ppmImage, struct ppmHeader * ppmHeader);





#endif
