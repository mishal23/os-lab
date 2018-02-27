#include "stdio.h"
#include "string.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "syslog.h"
#include "stdlib.h"
#include "errno.h"
#include "arpa/inet.h"
#include "unistd.h"

#define SERVER "0.0.0.0"
#define PORT 3000
#define MAX_LISTEN_NUM 5
#define BUFLEN 2048

int main()
{
    int flag = 0;
    int socket_filedescriptor;
    long recv_sent_bytes;
    char *buffer;
    char receive_data[BUFLEN];
    char send_data[BUFLEN];
    struct sockaddr_in *serverAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    
    socket_filedescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_filedescriptor < 0)
    {
        perror("error creating socket");
        return 0;
    }
    printf("Client started\n\n");

    serverAddr->sin_family = AF_INET;
    inet_aton(SERVER, (struct in_addr *)&(serverAddr->sin_addr));
    serverAddr->sin_port = htons(PORT);
    
    if(connect(socket_filedescriptor, (struct sockaddr *)serverAddr, sizeof(*serverAddr)) < 0)
    {
        perror("error connecting to server");
        return 0;
    }
    
    while(1)
    {
        if(!flag)
        {
            buffer = send_data;
            printf("\nCLIENT: ");
            fgets(send_data, BUFLEN, stdin);
        
            recv_sent_bytes = send(socket_filedescriptor, buffer,  strlen(send_data) + 1, 0);
            flag = 1;
        }
        else
        {
            buffer = receive_data;
            recv_sent_bytes = recv(socket_filedescriptor, buffer, BUFLEN, 0);
            printf("\nMESSAGE FROM SERVER: %s",receive_data);
            flag = 0;
        }
    }
    return 0;

}