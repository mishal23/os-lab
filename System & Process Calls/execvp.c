#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	printf("Started execlvp() file\n");
    execlp("./1","./1",NULL);

    printf("\nThis statment won't be executed\n");
    return 0;
}
