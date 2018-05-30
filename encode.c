/*
________________________________________________________________________________
    
    Damion Anderson
    CPSC1020 Sm2018
    daander@clemson.edu
________________________________________________________________________________
*/

#include "encode.h"

/*
    Even though we will not have comments in our PPM file, I wrote this
    algorithm to be portable. Meaning it can be used with any PPM header,
    regardless of format. In my research, there were mainly 3 different header
    formats - formats meaning the order of P6, #, Height, Width, Max. This
    algorithm will catch for each variation.
*/


void readHeader(FILE * ppmImage, struct header_t * ppmPtr)
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

    i++;

    while (header[i] != ' ' && header[i] != '\n')
    {
        height[k] = header[i];
        i++, k++;
    }


    sscanf(width, "%d", &ppmPtr->col);
    sscanf(height, "%d", &ppmPtr->row);
    ppmPtr->maxColor = 255;


}

/*
                        Function Description:
    The function begins with a do-while loop. I tried to write the program where
    this wasn't necessary; however, I kept getting inconsistent results.
    Therefore, I implemented an algorithm that rechecks for the header. I have
    a counter called "headerItems". The do-while loop continues until the
    counter hits 4 - P6, Col, Row, Max Color. Then it jumps into the function
    to grab pixel data and throw it into my double pointer array.

*/


struct pixel_t ** readPixel(FILE *ppmImage, struct header_t *ppmHeader)
{
    int i = 0, j = 0;
/*
    After the do-while loop, I am allocating memory for the array and then grab
    the pixel data.
*/
    struct pixel_t ** arr = (struct pixel_t **) malloc(ppmHeader->row * 
                            sizeof(struct pixel_t*));


    for (i = 0; i < ppmHeader->row; i++)
    {
        arr[i] = (struct pixel_t *) malloc(ppmHeader->col * 
                    sizeof(struct pixel_t));
    }


    for (i = 0; i < ppmHeader->row; i++)
    {
        for (j = 0; j < ppmHeader->col; j++)
        {
            fscanf(ppmImage, "%c%c%c", &arr[i][j].r, &arr[i][j].g, 
                    &arr[i][j].b);
        }
    }
    
    return arr;
}

void writeHeader(struct header_t * ppmPtr)
{
    fprintf(stdout,"P6\n%d %d\n%d\n", ppmPtr->col, ppmPtr->row, 
        ppmPtr->maxColor);
}

void writePixels(struct pixel_t ** arr, struct header_t * ppmPtr, int col, 
    int arrInt[][col])
{
/*
    This function is just adding the encrypted message to the pixel array
    that will be written to the terminal.   
*/
    int i = 0, j = 0, k = 0;

    for (i = 0; i < col; i++)
    {
        do
        {
            arr[i][j].r += arrInt[i][k];           
            k++;
            arr[i][j].g += arrInt[i][k];
            k++;
            arr[i][j].b += arrInt[i][k];
            k++;
            j++;
        }while (k != 9);
        k = 0;
    }

/*
    This portion is simply printing the encoded message to the terminal. 
*/

    for (i = 0; i < ppmPtr->row; i++)
    {
        for (j = 0; j < ppmPtr->col; j++)
        {
            printf("%c%c%c", arr[i][j].r, arr[i][j].g, arr[i][j].b);
        }
    }
    
}


void removeDigit(struct pixel_t** arr, struct header_t* ppmPtr)
{

/*
    This algorithm is taking the remainder from % 10 and then subtracting the 
    remainder from the digit - effectively stripping the last digit of the 
    RGB value. I've printed this to the screen and it seems to be working. 
*/
    int i = 0, j = 0, red = 0, blue = 0, green = 0;
    for ( i = 0; i < ppmPtr->row; i++)
    {
        for ( j = 0; j < ppmPtr->col; j++)
        {
            red = arr[i][j].r % 10;
            arr[i][j].r -= red;
            green = arr[i][j].g % 10;
            arr[i][j].g -= green;
            blue = arr[i][j].b % 10;
            arr[i][j].b -= blue;
        }
    }
}

void dec2bin (int col, int row, int arrPtr[row][col], int arrInt[row])
{
    int i = 0, j = 0, k = 0, p = 8;
/*
    This took a while to develope. The hardest part was trying to figure out
    how to manage a 2D array when copying from a 1D array. The do-while loop
    was the best way I could figure out. 
*/
    for (i = 0; i < 7; i++)
    {
        do
        {
            arrPtr[i][8-j] = arrInt[k] % 2;
            arrInt[k] /= 2;
            j++;
        } while ((arrInt[k] >= 1) && (j !=8 ));
        k++;
        j = 0;
        
    }    
}

void encodeMsg(FILE * ppmImage, struct header_t * ppmPtr, struct pixel_t ** 
    arrPtr, char * msg)
{
    int i = 20, j = 0, cntr = 0, k = 9; 
    char * charPtr;

/*
    This is just grabbing the amount of characters in the message. I tried
    using strlen() as recommended, but the results were not correct. It was 
    adding 3 extra 0's, which would mess up the the encryption. 
*/


    for(i = 0; msg[i] != '\0'; i++)
    {
        cntr++;
    }

// I then use the cntr to create the 2D array for binary conversion.
    int intArr[cntr], bin[cntr][9];

/*
    This is going through character by character grabbing each's ASCII value. 
    I also snook a nested for-loop to initialize every element in the 2D arr
    to ensure consistent results.
*/

    for (i = 0; msg[i] != '\0'; i++)
    {
        intArr[i] = msg[i];
        //printf("intArr[i] = %d\n", intArr[i]);
        for (j = 0; j < 9; j++)
        {
            bin[i][j] = 0;
        }
    }

/*
    I then convert the message to binary in a 2D arr. This will be sent to 
    the pixel map. 
*/

    dec2bin( k, cntr, bin, intArr);

    removeDigit(arrPtr, ppmPtr);

    writeHeader(ppmPtr);

    writePixels(arrPtr, ppmPtr, k, bin);

}