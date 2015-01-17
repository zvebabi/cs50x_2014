#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void cifer(string a, int k[]);

int main(int argc, string argv[])
{
    //cheking for right input
    if (argc!=2)
    {
        printf("One argumet consist of char!\n");
        return 1;
    }
    for(int i=0; i<strlen(argv[1]); ++i)
    { 
        if(!isalpha(argv[1][i]))
        {
            printf("One argumet consist of nonchar!\n");
            return 1;
        }
    } 
    string plaintext;
    plaintext = GetString();
    int k[strlen(plaintext)];  //Vigenere key
    for(int i=0; i<strlen(argv[1]); ++i)// A or a=0, B or b = 1, C or c=2
    {
        if(isupper(argv[1][i]))
        {
            k[i]=argv[1][i]-'A';
        }
        if(islower(argv[1][i]))
        {
            k[i]=argv[1][i]-'a';
        }
    }
    //make a key lenght equal to plaintext
    for(int i = strlen(argv[1]), n = strlen(plaintext), j=0; i<n; ++i)
    {
        if(!isalpha(plaintext[i]))
        {
            k[i]=0;
        }
        else
        {
            k[i]=k[j];
            ++j;
            if(j==strlen(argv[1]))
            {
                j=0;
            }
        }
       
    }
    cifer(plaintext, k);
    return 0;
}

void cifer(string a, int k[])     //Cifer algorithm
{
    for(int i=0, n = strlen(a);i<n;++i)
    {
        if (isalpha(a[i]))
        {
            int temp = a[i]+k[i];
            if (islower(a[i]))
            {
                if(temp>122)
                {
                    temp -=26;
                }     
            }
            else
            {
                if(temp>90)
                {
                    temp -=26;
                }
            }            
            printf("%c", temp);
        }
        else
        {
            printf("%c", a[i]);
        }
    }
    printf ("\n");
}
