/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  B;
typedef struct
{
    B  first;
    B  second;
    B  third;
    B  forth;
} __attribute__((__packed__))
BEG;
typedef struct
{
    B  BYTE[512];
    
} __attribute__((__packed__))
BLOCK;
int main(void)
{
    char temp[8];
    int c = 0;
    FILE* jpg = NULL;
    FILE* card = fopen("card.raw", "r");
    BLOCK test;
    int l = fread(&test, sizeof(BLOCK), 1, card);
    while (l == 1)
    {

        if (test.BYTE[0] == 0xff && test.BYTE[1] ==0xd8 && test.BYTE[2] == 0xff && test.BYTE[3] == 0xe0)
        {
            if (c != 0)
            {
                fclose(jpg);
            }
            if (c < 10)
            {
                sprintf(temp, "00%d.jpg", c);
                jpg = fopen(temp, "w");
                fwrite(&test, sizeof(BLOCK), 1, jpg);
                c++;
            }
            else
            {
                sprintf(temp, "0%d.jpg", c);
                jpg = fopen(temp, "w");
                fwrite(&test, sizeof(BLOCK), 1, jpg);                
                c++;
            }   
        }
        else if (test.BYTE[0] == 0xff && test.BYTE[1] ==0xd8 && test.BYTE[2] == 0xff && test.BYTE[3] == 0xe1)
        {
            if (c != 0)
            {
                fclose(jpg);
            }
            if (c < 10)
            {
                sprintf(temp, "00%d.jpg", c);
                jpg = fopen(temp, "w");
            }
            else
            {
                sprintf(temp, "0%d.jpg", c);
                jpg = fopen(temp, "w");
            }  
        }
        else if (c != 0)
        {
            fwrite(&test, sizeof(BLOCK), 1, jpg);
        }
        l = fread(&test, 512, 1, card);
    }
        fclose(card);
}
