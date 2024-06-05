/******************************************************************************/
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
/******************************************************************************/
#define PORT 8080
#define MAXLINE 50
/******************************************************************************/
static void RunTcpClient();
/******************************************************************************/
int main()
{
	RunTcpClient();
	
    return 0;
}   
/******************************************************************************/
static void RunTcpClient()
{
	int sockfd;
	char buffer[MAXLINE];
	char* message = "PING TCP";
	struct sockaddr_in servaddr;

	int len;
	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
		printf("socket creation failed");
		exit(0);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	/* Filling server information */
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) 
    {
        printf("\n Error : Connect Failed \n");
    }
    
	socklen_t addrlen = sizeof(servaddr);
	
	send(sockfd, (const char*)message, strlen(message),0);
	
	recv(sockfd, (char*)buffer, MAXLINE, 0);
	
	sleep(1);
	printf("Message from server: ");
	puts(buffer);
        
    close(sockfd);
}
