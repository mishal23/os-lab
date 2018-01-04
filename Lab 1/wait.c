#include "stdio.h"
#include "sys/types.h"
#include "unistd.h"
#include "sys/wait.h"
int main()
{
	pid_t pid = fork();

	if (pid== 0)
        printf("-> Child process\n");
    else
    {
        printf("-> Parent process\n");
        wait(NULL);
        // this statement will always be executed at last due to wait()
        printf("-> Child process terminated\n");
    }
 
    printf("-> End\n");
    return 0;
}