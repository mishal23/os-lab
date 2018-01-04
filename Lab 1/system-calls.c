#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define path1 "/home/mishal23/Desktop/test1.txt"
#define path2 "/home/mishal23/Desktop/test2.txt"
void main()
{
	char string[100]="Content for the file";
	
	int filedescriptor1 = creat(path1,S_IRWXU);
	if(filedescriptor1<0)
		perror("Error");
	else
		printf("File created: %d\n",filedescriptor1 );

	// open() system call
	int filedescriptor = open(path1,O_CREAT | O_RDWR,S_IRWXU);
	if(filedescriptor<0)
		perror("Error");
	else
		printf("File created: %d\n",filedescriptor );

	// write() system call
	int size_wrote = write(filedescriptor,string,strlen(string));
	if(size_wrote<0)
		perror("error");
	else
		printf("Content :%s \nwritten to file with size %d\n",string,size_wrote );

	// lseek() system call
	lseek(filedescriptor,0,SEEK_SET);
	char buf[100];

	// read() system call
	int size_read = read(filedescriptor, buf, 100);

	buf[size_read]='\0';
	if(size_read<0)
		perror("error");
	else
		printf("String read: %d\n%s\n",size_read,buf);

	// dup() system call
	 int duplicated = dup(filedescriptor);

	 if(duplicated<0)
	 	perror("error");
	 else
	 	printf("Old Descriptor=%d\nNew Descriptor=%d\n",filedescriptor,duplicated);

	 // access() F_OK system call
	 int existing = access(path1,F_OK);
	 if(existing<0)
	 	perror("error");
	 else
	 	printf("File exists\n");
		
		 // access() R_OK system call
	 int read_permit = access(path1,R_OK);
	 if(read_permit<0)
	 	perror("error");
	 else
	 	printf("read permission\n");	 
	 // access() W_OK system call
	 int write_permit = access(path1,W_OK);
	 if(write_permit<0)
	 	perror("error");
	 else
	 	printf("write permission\n");
	 // access() X_OK system call
	 int execute_permit = access(path1,X_OK);
	 if(execute_permit<0)
	 	perror("error");
	 else
	 	printf("execute permission\n");

	 // link() system call
	 int linked = link(path1,path2);
	 if(linked!=0)
	 	perror("error");
	 else
	 	printf("Link created successfully\n");

	// chmod() system call 
	int chmod_permit = chmod(path1,S_IRWXG| S_IRWXU);
	if(chmod_permit<0)
		perror("error");
	else
		printf("RWX permission to group given\n");

	// chown() system call
	int chown_permit = chown(path1,1002,1002);
	if(chown_permit<0)
		perror("error");
	else
		printf("student is the new owner\n");

	// umask() system call
	/*
	int old_mask = umask(S_IWOTH);
	if(old_mask<0)
		perror("error");
	else
		printf("Previous mask value: %d\n",old_mask );
	*/

	 // unlink() system call
	 int unlinked = unlink(path2);
	 if(unlinked!=0)
	 	perror("error");
	 else
	 	printf("UnLink done successfully\n");

	// close() system call
	int closed = close(filedescriptor);
	if(closed<0)	
		perror("error");
	else
		printf("File closed successfully\n");

	
}