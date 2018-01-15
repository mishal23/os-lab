#include<stdio.h>
#include "stdlib.h"
void main()
{
    int number,i;
    printf("Enter any number: ");
    scanf("%d",&number);

    if(number<=2 || number>=50)
        goto end;
    else
    {
        for(i=1;i<number;i++)
        {
            printf("%d\n",i);
            if(i==(number/2))
            {
                printf("Program exiting\n");
                exit(0);
            }
        }
    }
    end:
        printf("choose number between 2-50\n");
}