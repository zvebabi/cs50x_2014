#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do 
    {
        printf("Height: ");
        h = GetInt();
    }
    while (h < 0||h > 23);  //cheking of right number
    
    
    for (int r=1; r<=h; r++)  // building of pyramde
    {
        int s1=h-r; //number of spaces
        int k1=r; //number of hashes
        int s2=h-r; //number of spaces
        int k2=r; //number of hashes
        while(s1>0)
        {
            printf(" ");
            s1--;
        } 
        
        while(k1>0)
        {
            printf("#");
            k1--;
        }
        
        printf("  ");
        
        while(k2>0)
        {
            printf("#");
            k2--;
        } 
        
        while(s2>0)
        {
            printf(" ");
            s2--;
        } 
        
        printf("\n");   
    }
    printf( " #  # \n##  ##\n");
}
