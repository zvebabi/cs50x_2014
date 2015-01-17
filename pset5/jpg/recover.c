/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

typedef uint8_t BYTE;
typedef struct
{
    BYTE buff[512];
} __attribute__((__packed__))
BUFFER;

int main(int argc, char* argv[])
{
    BUFFER bf;
    char title[10];
    int jpgnum = 0;
    int new_jpg=0, start_write=0;
    FILE* img;
    //open file
    FILE* cardraw=fopen("card.raw", "r");
    if(cardraw == NULL)
    {
        printf("Could not open the fail %s", "card.raw");
        return 1;
    }
    
    while(!feof(cardraw))
    {        
        fread(&bf, sizeof(BUFFER), 1, cardraw);
        if(!feof(cardraw))
        {
            if (bf.buff[0] == 0xff && bf.buff[1] == 0xd8 && bf.buff[2] == 0xff && (bf.buff[3] ==  0xe0 || bf.buff[3] ==  0xe1))
            {
                if(new_jpg)
                {
                    fclose(img);
                    jpgnum++;
                }
                sprintf(title, "%03d.jpg", jpgnum);
                img = fopen(title, "a");
                new_jpg=1;
                start_write=1; 
            }
            if(start_write)
            {    
                fwrite(&bf, sizeof(BUFFER),1, img);
            }
        }
    }
    fclose(cardraw);
    fclose(img);
    return 0;
}
