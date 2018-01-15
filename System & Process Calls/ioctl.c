/*
    Code taken from :- 
    https://gist.github.com/akoskovacs/832c87e37e56394b2d461a632938b21c
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <linux/cdrom.h>

#define CDROM_DEV "/dev/cdrom"
int eject(int fd_dev)
{
    int cmds[] = { CDROMEJECT, CDROMEJECT_SW };
    int i, ret;
    for (i=0;i<sizeof(cmds)/sizeof(int); i++) 
    {
       ret = ioctl(fd_dev, cmds[i], 0);
       if (ret < 0) 
       {
            perror("ioctl()");
       }
    }
    return ret;
}

int main(int argc, const char *argv[])
{
    int fd;
    const char *dev = CDROM_DEV;
    if (argv[1]) 
    {
        dev = argv[1];
    }
    
    fd = open(dev, O_RDONLY|O_NONBLOCK);
    if (fd <= 0) 
    {
        perror("open()");
        return 1;
    }
    eject(fd);
    close(fd);
    return 0;
}