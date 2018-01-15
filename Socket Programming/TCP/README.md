### TCP (Transmission Control Protocol)
- TCP provides a connection oriented service, since it is based on connections between clients and servers.
- TCP provides reliability. When a TCP client send data to the server, it requires an acknowledgement in return. If an acknowledgement is not received, TCP automatically retransmit the data and waits for a longer period of time.
- TCP is instead a byte-stream protocol, without any boundaries at all.

### **Points:**
- Why is ***MAX_LISTEN_NUM*** set to 5?

  The first argument in ``listen()`` is the socket file descriptor, and the second is the size of the backlog queue, i.e., the number of connections that can be waiting while the process is handling a particular connection. This should be set to 5, the maximum size permitted by most systems.

- What does ```inet_aton()``` do?

  It converts the Internet host address cp from  the  IPv4  numbers-and-dots  notation  into  binary  form (in network byte order) and stores it in the structure that inp points to.

### Running the programs
If you  want to run the programs on different PC's with same internet, find out the IP address of the PC on which server is going ot be run and change the IP address in ```#define SERVER "new_ip"``` in ```client.c```
- Compile the codes

  ```gcc -o client client.c```<br>
  ```gcc -o server server.c```

- Run the executables (server first)
