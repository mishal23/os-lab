### UDP (User Datagram Protocol)
- UDP is a simple transport-layer protocol. The application writes a message to a UDP socket, which is then encapsulated in a UDP datagram, which is further encapsulated in an IP datagram, which is sent to the destination.
- There is no guarantee that a UDP will reach the destination, that the order of the datagrams will be preserved across the network or that datagrams arrive only once.
- The problem of UDP is its lack of reliability: if a datagram reaches its final destination but the checksum detects an error, or if the datagram is dropped in the network, it is not automatically retransmitted.
- Each UDP datagram is characterized by a length. The length of a datagram is passed to the receiving application along with the data.
- No connection is established between the client and the server and, for this reason, we say that UDP provides a connection-less service.

### Running the programs
If you  want to run the programs on different PC's with same internet, find out the IP address of the PC on which server is going ot be run and change the IP address in ```#define SERVER "new_ip"``` in ```client.c```
- Compile the codes

  ```gcc -o client client.c```<br>
  ```gcc -o server server.c```

- Run the executables (server first)
