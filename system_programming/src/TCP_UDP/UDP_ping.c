/******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h> //struct sockaddr_in
/******************************************************************************/
#define PORT      8080
#define BUFF_LEN  20
#define INIT      0
#define INFINITE  1
/******************************************************************************/
int main()
{
    int sockfd;
    char buffer[BUFF_LEN] = {INIT};
    struct sockaddr_in serv_addr, cli_addr;

    /* create a socket - For UDP -> SOCK_DGRAM */
    sockfd = socket(AF_INET, SOCK_DGRAM, INIT);
    /* set socket values to zero */
    memset(&serv_addr, INIT, sizeof(serv_addr));
    /* set the address family, IP address, and port number */
    /*THIS BLOCK CAN BE SIMILAR IN BOTH PROGRAMS CAUSE UDP*/
    /* AF_INET for IPV4 */
    serv_addr.sin_family = AF_INET;
    /* INADDR_ANY - SOCKET SHOULD BIND TO ALL AVAILABLE NETWORK INTERFACES */
    /* .sin_addr.s_addr -> It represents the IP of a socket in the Internet Protocol */
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    /* htons() - host byte order to network byte order*/
    serv_addr.sin_port = htons(PORT);
    /* bind the socket to the server address */
    bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    /*infinite loop*/
    while (INFINITE) 
    {
        
        socklen_t cli_len = sizeof(cli_addr);

        /* receive data from the client */
        recvfrom(sockfd, buffer, sizeof(buffer), INIT, 
                                    (struct sockaddr *) &cli_addr, &cli_len);

        sleep(1);

        printf("server Received: %s\n", buffer);

        strcpy(buffer, "pong");

        sendto(sockfd, buffer, sizeof(buffer), INIT, 
                                        (struct sockaddr *) &cli_addr, cli_len);
        
    }
    close(sockfd);

    return 0;
}
/******************************************************************************/