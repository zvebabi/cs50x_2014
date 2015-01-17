/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"
// counter of total word in dictionary
unsigned int total_words=0;

/*
 *  Make a hash for dictionary word
 */
int hash_func(const char* s)
{
    int i=0;
    while( s[i]!='\0')
    {
        
        hash[i]=s[i]-'a';//just shift ascii to 97 position left
        i++;
    }
    hash[i]='\0'; //terminate hash
    return i; //return length of word
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //lower case for all word
    int k=0;
    while( word[k]!='\0')
    {
        word_d[k]=tolower(word[k]);
        k++;
    }
    word_d[k]='\0'; //terminate word
    
    // hash word from text
    int s=hash_func(word_d);
    node* temp = root;  //take a cursor
    for(int i=0; i<s; i++)
    {
        //find of word in tries struct
        if(temp->children[hash[i]]==NULL)
        {
            #ifdef DEBUG
            printf("bad word, dictionary.c:39\n");
            #endif
            return false;
        }
        temp = temp->children[hash[i]]; //go to next node(next character)
    }
    //check flag for really word
    if(temp->is_word==true)
    {
        #ifdef DEBUG
        printf("god word, dictionary.c:48\n");
        #endif
        return true;
    }
    else
    {
        #ifdef DEBUG
        printf("bad word, dictionary.c:48\n");
        #endif
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary
    FILE* dict=fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Cant't open dictionary file: %s\n", dictionary);
        return false;
    }
    #ifdef DEBUG
    printf("dictionary %s is open\n", dictionary);
    #endif
    //allocate memory for dictionary
    root=malloc(sizeof(node));
    node* temp = root;
    while(fscanf(dict, "%s\n", word_d) != EOF)
    {
        //convert word_d to hash and take a length of word_d
        int s=hash_func(word_d);
        for (int i=0; i< s; i++)
        {
            if(temp->children[hash[i]]==NULL)
            {
                temp->children[hash[i]]=malloc(sizeof(node));
            }
            temp = temp->children[hash[i]];
        }
        temp->is_word=true;
        ++total_words;
        temp = root;
    }
    fclose(dict);
    #ifdef DEBUG
    printf("ALL word is load\n");
    #endif
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return total_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    if(memfree(root))
        return true;
    return false;
}

/**
 * Recursion function for clearing memory. Returns true if successful else false.
 */
bool memfree (node* temp)
{
   for (int i=0; i<=27;i++)
    {
        if (temp->children[i] != NULL)
        {
            memfree(temp->children[i]);
        }
        else if(i==26)
        {
            free(temp);
            return true;
        }
    }

    #ifdef DEBUG
    printf("false in memfree\n");
    #endif
    return true;
}
