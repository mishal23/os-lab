#include "stdio.h"
#include "string.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "stdlib.h"
#include "syslog.h"
#include "errno.h"
#include "unistd.h"

#define SERVER "0.0.0.0"
#define PORT 3000
#define MAX_LISTEN_NUM 5
#define BUFLEN 2048

int main()
{
    int flag = 0;
    int socket_filedescriptor;
    int accepted_descriptor;

    int recv_sent_bytes;
    char *buffer;
    char send_data[BUFLEN];
    char receive_data[BUFLEN];
    
    struct sockaddr_in *serverAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    struct sockaddr_in *clientAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    socklen_t clientSocketLength = sizeof(*clientAddr);
    
    socket_filedescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_filedescriptor < 0)
    {
        perror("error creating socket");
        return 0;
    }

    printf("\nServer started\n\n");

    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htons(PORT); 
    serverAddr->sin_addr.s_addr = htonl(INADDR_ANY); 
    
    
    if(bind(socket_filedescriptor, (struct sockaddr *)serverAddr, sizeof(*serverAddr)) < 0)
    {
        perror("bind error");
        return 0;
    }
    if(listen(socket_filedescriptor, MAX_LISTEN_NUM) < 0)
    {
        perror("error marking socket as passive");
        return 0;
    }
    
    accepted_descriptor = accept(socket_filedescriptor, (struct sockaddr *)clientAddr, &clientSocketLength);
    if(accepted_descriptor < 0)
    {
        perror("error accepting the incoming connection");
        exit(1);
    }
    
    printf("Client connected\n\n");
    while(1)
    {
        if(!flag) 
        {
            buffer = receive_data;
            recv_sent_bytes = recv(accepted_descriptor, buffer, BUFLEN, 0);
            printf("\nMESSAGE FROM CLIENT: %s",receive_data);
            flag = 1;
        }
        else
        {
            printf("\nSERVER: ");
            fgets(send_data, BUFLEN, stdin);
            buffer = send_data;
            recv_sent_bytes = send(accepted_descriptor, buffer, strlen(send_data) + 1, 0);
            flag = 0;
        }
    }
    return 0;
}
