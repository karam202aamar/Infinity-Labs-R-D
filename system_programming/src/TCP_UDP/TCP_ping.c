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
#define SA        struct sockaddr
/******************************************************************************/
int main()
{
    int sockfd, connfd;
    char buffer[BUFF_LEN] = {INIT};
    struct sockaddr_in serv_addr, cli_addr;
    ssize_t ret;
    /* create a socket - For TCP -> SOCK_STREAM */
    sockfd = socket(AF_INET, SOCK_STREAM, INIT);
    /* set socket values to zero */
    memset(&serv_addr, INIT, sizeof(serv_addr));
    /* set the address family, IP address, and port number */
    /* AF_INET for IPV4 */
    serv_addr.sin_family = AF_INET;
    /* INADDR_ANY - SOCKET SHOULD BIND TO ALL AVAILABLE NETWORK INTERFACES */
    /* .sin_addr.s_addr -> It represents the IP of a socket in the Internet Protocol */
    serv_addr.sin_addr.s_addr = INADDR_ANY;//here
    /* htons() - host byte order to network byte order*/
    serv_addr.sin_port = htons(PORT);
    /* bind the socket to the server address */
    bind(sockfd, (SA*)&serv_addr, sizeof(serv_addr));
    
    if ((listen(sockfd, 5)) != 0) 
    {
        printf("Listen failed...\n");
        return 1;
    }
    
    int len = sizeof(cli_addr);
 
    connfd = accept(sockfd, (SA*)&cli_addr, &len);
 
    /*infinite loop*/
    while (INFINITE) 
    {
        ret = read(connfd, buffer, BUFF_LEN);
        if (ret == -1) 
        {
            printf("failed\n");
        }
        sleep(1);
        printf("server Received: %s\n", buffer);

        strcpy(buffer, "pong");
        ret = write(connfd, buffer, BUFF_LEN);
        if (ret == -1) 
        {
            printf("failed\n");
        }
    }
    close(sockfd);

    return 0;
}
/******************************************************************************/