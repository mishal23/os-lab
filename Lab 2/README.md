# Socket Programming
Socket programming is a way of connecting two nodes on a network to communicate with each other.

### Basics
- To create a socket,we need to specify the address domain and the socket type.
	- Address Domains:
	
		1) unix domain - two processes which share a common file system communicate. [Constant used: **AF_UNIX**]
		2) internet domain - two processes running on any two hosts on the Internet communicate. [Constant used: **AF_INET**]
	- Socket type:

		1) stream sockets - communications as a continuous stream of characters [Constant used: **SOCK_STREAM**]
		
		2) datagram sockets - read entire messages at once [Constant used: **SOCK_DGRAM**]
		
- Port numbers are 16 bit unsigned integers.
- The lower numbers are reserved in Unix for standard services. eg. the port number for the FTP server is 21.
- Stream sockets use TCP (Transmission Control Protocol), which is a reliable, stream oriented protocol.
- Datagram sockets use UDP (Unix Datagram Protocol), which is unreliable and message oriented.
- ```#include <sys/socket.h>``` : Includes a number of definitions of structures needed for sockets.
- ```#include <netinet/in.h>``` : Contains constants and structures needed for internet domain addresses.
- A sockaddr_in is a structure containing an internet address. This structure is defined in header **netinet/in.h**

```c
struct sockaddr_in{
  	short   sin_family; /*  a code for the address family */
  	u_short sin_port;	/*  port number */
  	struct  in_addr sin_addr;	/* IP address of the host */
  	char    sin_zero[8]; /* Not used, must be zero */
};
```

- An in_addr structure, defined in the same header file, contains only one field, a unsigned long called s_addr.

###  Functions
- ```htons()```/```htonl()``` :- We cannot directly copy port no to sin_port field, it is necessary to convert it to network byte order using the function ```htons()``` which converts a port number in host byte order to a port number in network byte order.

	- ```htons()``` is used for 16 bits
	- ```htonl()``` is used for 32 bits.
- ```bind()``` :- When scoket is created it exists in a name space (address family) but has no address assigned to it.  ```bind()``` assigns the    address  specified  by  addr  to  the  socket  referred  to by the file descriptor sockfd.
- ```listen()``` :- The ```listen()``` system call allows the process to listen on the socket for connections.
- ```accept()``` :- The ```accept()``` system call causes the process to block until a client connects to the server. It returns a new file descriptor.
- ```connect()``` :- The ```connect()``` function is called by the client to establish a connection to the server

### FAQs
- Datagram : A datagram is a unit of transfer assoicated with networking. Data is frequently divided into smaller pieces and transmitted without a defined route or guaranteed order of delivery. A datagram is primarily used for wireless communication and is self-contained with source and destination addresses written in the header.
	- **Is datagram similar to packet?** It is similar to a packet, which is a small piece of data transmitted through a connectionless protocol; but a datagram cannot handle prior or subsequent data communication.


- Why is ```sendto()```, ```recvfrom()``` used for UDP
and ```recv()```, ```send()``` used for TCP?

	1. ```accept()``` is for **TCP**. It has nothing to do with **UDP**.

	2. ```connect()``` in UDP doesn't do anything to the other end, it just conditions the local API to know who you are sending to and receiving from.

	3. If you want to send to multiple destinations with the same socket, you don't use ```connect()```, you use ```sendto()``` instead. Similarly for receiving.

		Consider a UDP server for example. It would call ```recvfrom()```, so it would get the source address information, process the request, create the response, and send it to that address via ```sendto()``` . No ```connect()``` involved anywhere, therefore not possible to use either ```send()``` or ```recv()```.

	4. It is only necessary to ```bind()``` a server, because the clients need a fixed port number to send to. A client needn't ```bind()``` at all: an automatic ```bind()``` will take place on the first ```send()```/ ```sendto()```/ ```recv()```/ ```recvfrom()``` using a system-assigned local port number.

-----------------------------------------------------

- Summarizing, since TCP requires a connection, it needs the following APIs on server and client<br>
 ***server*** : ```socket()```, ```bind()```, ```listen()```, ```accept()```, ```recv()```, ```send()```<br>
 ***client*** : ```socket()```, ```connect()```, ```send()```, ```recv()```

 	And since UDP is a connectionless protocol, it does not require **connect()** on the client and **listen()** and **accept()** on the server.<br>
 	***server*** : ```socket()```, ```bind()```, ```recvfrom()```, ```sendto()```<br>
 	***client*** : ```socket()```, ```sendto()```, ```recvfrom()```
