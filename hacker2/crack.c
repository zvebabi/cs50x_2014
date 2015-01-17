#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



const int SALT_LENGHT = 2;
const int MAX_PASSWD_SIZE = 9;

int try_pass(char salt[SALT_LENGHT],  char word[MAX_PASSWD_SIZE],string argv[]);
void brutforse(char salt[SALT_LENGHT], string argv[]);

int main(int argc, string argv[])
{
    if(argc!=2)
    {
        printf("only one argument!\n");
        return 1;
    }
    char salt[SALT_LENGHT];
    for (int i=0; i<SALT_LENGHT;i++)
    {
        salt[i]=argv[1][i];
    }
    printf("Key is %c%c\n", salt[0],salt[1]);
    brutforse(salt, argv);
    return 0;
}

int try_pass(char salt[SALT_LENGHT], char word[MAX_PASSWD_SIZE],string argv[])
{
    if (strcmp ( crypt(word,salt) , argv[1]) == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void brutforse(char salt[SALT_LENGHT],string argv[])
{
    char word[MAX_PASSWD_SIZE]; // supposed passwd
    FILE *text;
    char *eword;  // chek word before testing for opening 
    text = fopen("/usr/share/dict/words", "r"); //open file
    if (text == NULL)
    {
        printf("Can't open file!\n");
        return;
    }
    else
    {
        printf("Start reading... \n");
    }
    int i=0;
    while(!i)
    {
        eword = fgets(word, MAX_PASSWD_SIZE, text);
        
        if (eword == NULL)  // check for error or end of file
        {
            if (feof(text) !=0)
            {
                printf("End of file!\n");
                break;
            }
            else
            {
                printf("Error of reading file!\n");
                break;
            }
        }
        i = try_pass(salt, word, argv);
        if (i==1)
        {
            printf ("Closing file...");
            if ( fclose (text) == EOF)
            {
                printf ("Error of closing file.\n");
            }
            else 
            {
                printf ("File is closed.\n");
            }
            printf("Password is: %s\n", word);
        }        
    }    
}











