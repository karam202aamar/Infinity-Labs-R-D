/******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/******************************************************************************/
#define PORT      8080
#define BUFF_LEN  20
#define INIT      0
#define INFINITE  1
#define SA        struct sockaddr
/******************************************************************************/
int main()
{
    int sockfd;
    char buffer[BUFF_LEN] = {INIT};
    struct sockaddr_in serv_addr;
    ssize_t ret;
    
    /* create a socket - For TCP -> SOCK_STREAM */
    sockfd = socket(AF_INET, SOCK_STREAM, INIT);
    /* set socket values to zero */
    memset(&serv_addr, INIT, sizeof(serv_addr));
    /* set the address family, IP address, and port number */
    serv_addr.sin_family = AF_INET;
    /* set port */
    serv_addr.sin_port = htons(PORT);
    /*
      convert the string "192.168.52.163" into the binary representation of 
      the IP address and store it in the sin_addr field
    */
    inet_pton(AF_INET, "192.168.52.163", &serv_addr.sin_addr);
    
    /* connect the client socket to server socket */
    if (connect(sockfd, (SA*)&serv_addr, sizeof(serv_addr))!= 0) 
    {
        printf("connection with the server failed\n");
        return 1;
    }

    while (INFINITE) 
    {
        strcpy(buffer, "ping");
        
        ret = write(sockfd, buffer, BUFF_LEN);
        if (ret == -1) 
        {
            printf("failed1\n");
        }
        ret = read(sockfd, buffer, BUFF_LEN);
        if (ret == -1) 
        {
            printf("failed2\n");
        }
        sleep(1);
        printf("client Received: %s\n", buffer);
    }
    close(sockfd);

    return 0;
}
/******************************************************************************/

#if 0
note : old version 
int main()
{
    int sockfd;
    char buffer[BUFF_LEN] = {INIT};
    struct sockaddr_in serv_addr;

    /* create a socket - For TCP -> SOCK_STREAM */
    sockfd = socket(AF_INET, SOCK_STREAM, INIT);
    /* set socket values to zero */
    memset(&serv_addr, INIT, sizeof(serv_addr));
    /* set the address family, IP address, and port number */
    serv_addr.sin_family = AF_INET;
    /*loopback address*/
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);

    /* connect the client socket to server socket */
    if (connect(sockfd, (SA*)&serv_addr, sizeof(serv_addr))!= 0) 
    {
        printf("connection with the server failed...\n");
        return 1;
    }

    while (INFINITE) 
    {
        strcpy(buffer, "ping");
        
        write(sockfd, buffer, BUFF_LEN);
        read(sockfd, buffer, BUFF_LEN);
        
        sleep(1);
        printf("client Received: %s\n", buffer);
    }
    close(sockfd);

    return 0;
}
#endif