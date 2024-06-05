/******************************************************************************/
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
/******************************************************************************/
#define PORT 8080
#define MAXLINE 50
/******************************************************************************/
static void RunUdpClient();
/******************************************************************************/
int main()
{
	RunUdpClient();
	
	return 0;
}
/******************************************************************************/
static void RunUdpClient()
{
	int sockfd, i;
	char buffer[MAXLINE];
	char* message = "PING UDP";
	struct sockaddr_in servaddr;

	int len;
	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("socket creation failed");
		exit(0);
	}

	memset(&servaddr, 0, sizeof(servaddr));


	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    for(i = 0; i < 5; ++i)
    {   
        socklen_t addrlen = sizeof(servaddr);
        
	    sendto(sockfd, (const char*)message, strlen(message),
		                0, (const struct sockaddr*)&servaddr,sizeof(servaddr));
	    printf("Message from server: ");
	    recvfrom(sockfd, (char*)buffer, MAXLINE, 0, (struct sockaddr*)&servaddr, &addrlen);
        sleep(1);
	    puts(buffer);
    }
	
	close(sockfd);
}