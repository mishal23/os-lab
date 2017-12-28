#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    execlp("gedit", "test.txt", NULL);
    printf("--This statement won't be executed--\n");
     
    return 0;
}