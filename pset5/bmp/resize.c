/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * REsize a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    else if(atoi(argv[1])<=0 || atoi(argv[1]) >100)
    {
        printf("n must be positive, less than or equal to 100\n");
        return 5;
    }

    // remember filenames
    int key = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    

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
    BITMAPFILEHEADER bf, temp_bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    temp_bf = bf;
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, temp_bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    temp_bi = bi;
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    /***** chang FILE/info headers  ****/
    //height and width
    temp_bi.biWidth *=key;
    temp_bi.biHeight *=key;
    
    // determine padding for scanlines outfile
    int out_padding =  (4 - (temp_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //area
    temp_bi.biSizeImage = abs(temp_bi.biHeight) * (temp_bi.biWidth * sizeof(RGBTRIPLE)+out_padding);
    // bfSize = size of bf(14)+ bi(40) +biSizeIm(^)
    temp_bf.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+temp_bi.biSizeImage;
    
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&temp_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&temp_bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // determine padding for scanlines infile
    int in_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for(int m = 0; m<key; m++)
        {
            //shift cursor for repeate line key times
            fseek(inptr, i*(bi.biWidth*sizeof(RGBTRIPLE)+in_padding)+54, SEEK_SET);
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                for(int l=0; l< key; l++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add paddle in outfile
            for (int k = 0; k < out_padding; k++)
            {
                fputc(0x00, outptr);
            }

        }
        // skip over padding, if any
//        fseek(inptr, in_padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
