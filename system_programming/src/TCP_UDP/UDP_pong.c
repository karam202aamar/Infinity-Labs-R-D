/******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
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
    struct sockaddr_in serv_addr;

    /* create a socket - For UDP -> SOCK_DGRAM */
    sockfd = socket(AF_INET, SOCK_DGRAM, INIT);
    /* set socket values to zero */
    memset(&serv_addr, INIT, sizeof(serv_addr));
    /* set the address family, IP address, and port number */
    /*THIS BLOCK CAN BE SIMILAR IN BOTH PROGRAMS CAUSE UDP*/
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    while (INFINITE) 
    {
        strcpy(buffer, "ping");

        socklen_t addrlen = sizeof(serv_addr);

        sendto(sockfd, buffer, sizeof(buffer), INIT, 
                                    (struct sockaddr *) &serv_addr, addrlen);

        recvfrom(sockfd, buffer, sizeof(buffer), INIT,
                                     (struct sockaddr *) &serv_addr, &addrlen);

        sleep(1);
        
        printf("client Received: %s\n", buffer);
    }
    close(sockfd);

    return 0;
}
/******************************************************************************/