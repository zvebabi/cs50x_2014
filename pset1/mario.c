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
        int s=h-r; //number of spaces
        int k=r+1;//number of hashes
        while(s>0)
        {
            printf(" ");
            s--;
        } 
        
        while(k>0)
        {
            printf("#");
            k--;
        } 
        
        
        printf("  ");
        while(k>0)
        {
            printf("#");
            k--;
        } 

         
        
     printf("\n");   
    }
}
