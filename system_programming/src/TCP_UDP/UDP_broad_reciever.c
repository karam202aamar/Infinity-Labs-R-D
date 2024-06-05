/******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
/******************************************************************************/
#define PORT      8080
#define BUFF_LEN  100
#define INIT      0
#define SA        struct sockaddr
/******************************************************************************/
int main() 
{
    int sockfd;
    char buffer[BUFF_LEN];
    socklen_t addrlen;
    struct sockaddr_in reciever;
    
    /* CREATE A SOCKET */
    sockfd = socket(AF_INET, SOCK_DGRAM, INIT);
    
    /* set socket values to zero */
    memset(&reciever, INIT, sizeof(reciever));
    /* set the address family, IP address, and port number */
    reciever.sin_family = AF_INET;
    reciever.sin_port = htons(PORT);
    reciever.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr*)&reciever, sizeof(reciever));

    addrlen = sizeof(reciever);
    /*recieve the broad cast message*/
    recvfrom(sockfd, buffer, sizeof(buffer), INIT, (SA*) &reciever, &addrlen);
 
    printf("You Received a broadcast message: %s\n", buffer);

    close(sockfd);

    return 0;
}
/******************************************************************************/