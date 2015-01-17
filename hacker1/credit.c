#include <stdio.h>
#include <cs50.h>
#include <math.h>

int number_digits (long long n);

int main (void)
{
    long long card, temp;
    int k = 0,d,l, m=0,sum=0;
    do  //cheking of right input
    {
        printf("Number: ");
        card = GetLongLong();
    }
    while (card<(000000000000)||card>(9999999999999999));

    //number of digit
    int i=number_digits(card);
    //make of array 
    int card_array[i];

 //  printf("i is a %i\n", i);    //debug

    temp = card;
    
    while(temp>0)
        {
        d=temp%10;
        temp=temp/10;
        card_array[k++]=d;        
        }
/*    //debug
    printf("Card number is: ");
    for (int j=0;j<=i;j++)
    {
        printf("%i",card_array[j]);
    }  
    printf("\n");
    **************************/
    
    //sum calculation(step1)
    for(int l=i-1;l>=0;l-=2)
    {
//       printf("(step1)l is %i\n",l);       //debug
        m = card_array[l]*2;
        if (m>=10)
            m=1+m%10;
        sum +=m;
 //       printf("(step1)sum is %i\n",sum);   //debug
    }
    //step 2
    l=i;
    while(l>=0)
    {
        sum +=card_array[l];
        l-=2;
//        printf("(step2)sum is %i\n",sum);   //debug
    }
    
  //defining of validity and bank
    int v=card_array[i]*10+card_array[i-1];
    int q=card_array[i];
        
    if (sum%5==0)   //validity of checksum
        {
        if(v>=50&&v<=55)
        printf("MASTERCARD\n");
        if(v==34||v==37)
        printf("AMEX\n");
        if(q==4)
        printf("VISA\n");      
        }
        
    else if(q==4)
        printf("VISA\n"); 
    else 
        printf("INVALID\n");      
    
}


int number_digits (long long n)
{
    int count=-1;
    while (n) {
        n/=10;
        count++; }
 
    return count;
}

