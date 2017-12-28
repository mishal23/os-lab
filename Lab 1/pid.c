#include <stdio.h>
#include <unistd.h>
int main()
{
	fork();
    pid_t pid = getpid();
    pid_t ppid = getppid();
    printf("Parent process id = %d\n",pid );
    printf("Child process with parent id = %d\n",ppid );

    return 0;
}