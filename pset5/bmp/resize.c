/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int mult = atoi(argv[1]);
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    BITMAPINFOHEADER nbi = bi;
    nbi.biHeight = bi.biHeight * mult;
    int h = nbi.biHeight;
    nbi.biWidth = bi.biWidth * mult;
    int w = nbi.biWidth;
    int npadding =  ((4 - (nbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4);
    int m = npadding*nbi.biWidth;
    nbi.biSizeImage = abs(((h*w) * 3)) + m;
    
    BITMAPFILEHEADER nbf = bf;
    nbf.bfSize = nbi.biSizeImage + 54;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&nbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&nbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    RGBTRIPLE array[nbi.biWidth];
    RGBTRIPLE triple;
    if (mult == 1)
    {
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
 
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }
    else
    {
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0, c =0; j < bi.biWidth; j++)
            {
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for (int x = 0; x < 2; x++)
                {
                    // write RGB triple to outfile
                    array[c] = triple;
                    c++;
                    
                }
            }
            for (int j = 0; j < mult; j++)
            {
                for (int x = 0; x < nbi.biWidth; x++)
                {
                    fwrite(&array[x], sizeof(RGBTRIPLE), 1, outptr);
                }
                fseek(inptr, padding, SEEK_CUR);
    
                for (int k = 0; k < npadding; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
    }
        // skip over padding, if any
        // then add it back (to demonstrate how)
    

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
