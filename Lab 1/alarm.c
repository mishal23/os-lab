#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int breakflag = 3;

void handle() 
{
    printf("Hello\n");
    breakflag--;
    alarm(1);
}

int main() 
{
    signal(SIGALRM, handle);
    alarm(1);
    while(breakflag) 
    {

    }
    printf("done\n");
    return 0;
}
