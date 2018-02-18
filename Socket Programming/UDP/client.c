#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "fcntl.h"
#include "unistd.h"
#include "string.h"

#define BUFLEN 2048
#define SERVER "0.0.0.0"
#define PORT 3000

char buffer[BUFLEN];


int main () 
{

	struct sockaddr_in *serverAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

	int socket_filedescriptor;
	socklen_t received_bytes;

	socklen_t socketServerLength = sizeof(*serverAddr);

	socket_filedescriptor = socket(AF_INET, SOCK_DGRAM, 0);
	if (socket_filedescriptor < 0) 
	{
		perror("error");
		return 0;
	}
	printf("Client Created\n");

	serverAddr->sin_family = AF_INET;
	serverAddr->sin_port = htons(PORT);

	inet_aton(SERVER, &serverAddr->sin_addr);

	memset(buffer, '\0', BUFLEN);

	while(1)
	{
		memset(buffer, '\0', BUFLEN);

		printf("\nCLIENT: ");
		fgets(buffer, BUFLEN, stdin);

		sendto(socket_filedescriptor, buffer, BUFLEN, 0, (struct sockaddr *)serverAddr, sizeof(*serverAddr));

		received_bytes = recvfrom(socket_filedescriptor, buffer, BUFLEN, 0, (struct sockaddr *)serverAddr, &socketServerLength);

		if (received_bytes == -1) 
		{

		} 
		else 
		{
			printf("\nMESSAGE FROM SERVER: %s", buffer);
		}

	}

}