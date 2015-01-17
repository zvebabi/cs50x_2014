/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"
#include <stdio.h>
//#define DEBUG

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int min=0, max=n-1, middle=(max-min)/2;
#ifdef DEBUG
printf("start_middle=%d, max=%d, min=%d\n", middle, max, min);
#endif
    while((max-min)>1)
    {
        if(value < values[middle])
        {
            max = middle;
            if((max-min)==1)
            {
                middle-=1;
            }
            middle -= (max-min)/2;
            #ifdef DEBUG
            printf("<middle=%d, max=%d, min=%d\n", middle, max, min);
            #endif
        }
        else if(value > values[middle])
        {
            min = middle;
            if((max-min)==1)
            {
                middle+=1;
            }
            else
            {
                middle += (max-min)/2;
            }
            #ifdef DEBUG
            printf(">middle=%d, max=%d, min=%d\n", middle, max, min);
            #endif
        }
        if(value==values[middle])
        {
            return true;
        }
    }
    return false;
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for(int i=0; i<n-1; ++i)
    {
        for (int j=i+1; j<n;++j)
        {
            if(values[j]<values[i])
            {
                int temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
    #ifdef DEBUG
    for(int i=0; i<n;++i)
    {
        printf("sort[%d]=%d\n", i, values[i]);
    }
    #endif
    return;
}










