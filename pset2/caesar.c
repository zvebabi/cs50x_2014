
/*  Caesar cipher */
   
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void cipher(string a, int k);
   
int main(int argc, char* argv[])
{
 /*cheking for right input of key*/   
    if (argc != 2)
    {
        printf("You should only have one argument!\n");
        return 1;
    }
    int key = atoi(argv[1]) % 26; // because k=1 and k=27 is equal (26 char in ABC)
    string plaintext;
    plaintext=GetString();
    cipher(plaintext, key);
    return 0;
}


void cipher(string a, int k)    //caesar cipher loop
{
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if (isalpha(a[i]))
        {
            int temp = a[i]+k;
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
    printf("\n");
}
