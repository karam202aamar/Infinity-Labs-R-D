#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
/******************************************************************************/
#define PORT       8080
#define BUFF_LEN   100
#define INIT       0
#define PERMITTED  1
#define SA        struct sockaddr
/******************************************************************************/
int main() 
{
    int sockfd;
    int broad_per = PERMITTED;
    char buffer[BUFF_LEN];
    struct sockaddr_in broad_args;

    /* CREATE A SOCKET */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    /* SET OPTIONS ON A SOCKET */
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broad_per, sizeof(broad_per));
    /* set socket values to zero */
    memset(&broad_args, 0, sizeof(broad_args));
    /* set the address family, IP address, and port number */
    broad_args.sin_family = AF_INET;
    broad_args.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    broad_args.sin_port = htons(PORT);
    
    strcpy(buffer, "HEY IT'S THE BROADCAST CHANNEL");
    /*SEND THE BROADCAST MESSAGE*/
    sendto(sockfd, buffer, BUFF_LEN, INIT, (SA*)&broad_args, sizeof(broad_args));

    close(sockfd);

    return 0;
}
/******************************************************************************/