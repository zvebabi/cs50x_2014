/* greedy by GregM */
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main (void)
{
    float f;
    int c, coins=0;
    printf("O hai!  ");
    do
    {
        printf( "How much change is owed?\n");
        f= GetFloat();
    }
    while (f<0);
    
    f=f*100.0;
    c = (int)round(f);  // convert dollars to cents
    
    if (c >= 25)
    { 
        coins = c/25;
        c = c%25;
    }
    if (c>=10)
    {
        coins+= c/10;
        c = c%10;      

    }
    if (c>=5)
    {
        coins+= c/5;
        c = c%5;
    }
    coins+= c;
    printf ("%d\n",coins);
}
