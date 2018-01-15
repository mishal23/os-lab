#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
	uid_t uid = getuid();
	uid_t euid = geteuid();
	if(uid==0 && euid==0)
		printf("Welcome root user\n");
	else
		printf("You aren't root\nuid=%d euid=%d\n",uid,euid);

	gid_t gid = getgid();
	gid_t egid = getegid();
	printf("gid=%d egid=%d\n",gid,egid );
}