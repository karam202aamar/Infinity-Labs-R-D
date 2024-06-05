/******************************************************************************/
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>
/******************************************************************************/
#define PORT 8080
#define MAXLINE 50
/******************************************************************************/
static void RunServer();
static int max(int x, int y);
/******************************************************************************/
int main()
{
    RunServer();

    return 0;
}
/******************************************************************************/
static void RunServer()
{
	/* define FD-networking (file descriptors) */
	int listenfd, connfd, udpfd, maxfdp, stdinfd;
    
	char buffer[MAXLINE];
	char input_str[MAXLINE];

	fd_set rset;
	ssize_t n;
	socklen_t len;

	struct sockaddr_in cliaddr, servaddr;

	char* message = "server pong";

	/*create TCP SOCKET*/
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
    /* set to zero */
	bzero(&servaddr, sizeof(servaddr));
    /* set the address family, IP address, and port number */
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	/* binding server addr structure to listenfd */
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(listenfd, 10);

	/*create UDP SOCKET*/
	udpfd = socket(AF_INET, SOCK_DGRAM, 0);
	/* binding server addr structure to udp sockfd */
	bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	/* set stdin file descriptor */
	stdinfd = STDIN_FILENO;

    bzero(buffer, sizeof(buffer));

	/* clear the set */
	FD_ZERO(&rset);

	/* get maxfd */
	maxfdp = max(listenfd, udpfd) + 1;

	while(1)
    {
		
        /* add a file descriptors to rset*/
        FD_SET(udpfd, &rset);
		FD_SET(listenfd, &rset);
		FD_SET(stdinfd, &rset);

		/* select the ready descriptor */
		select(maxfdp, &rset, NULL, NULL, NULL);
        
		/* if tcp socket is readable then handle */
		if (FD_ISSET(listenfd, &rset)) 
        {
			len = sizeof(cliaddr);
            
			connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
           
			n = recv(connfd, buffer, sizeof(buffer), 0);
     
            sleep(1);
            printf("Message from TCP client: ");
			puts(buffer);
          
			send(connfd, (const char*)message, sizeof(buffer), 0);
          
		}
		
		/* if udp socket is readable receive the message. */
		if (FD_ISSET(udpfd, &rset)) 
        {
            /* printf("333333\n"); */
			len = sizeof(cliaddr);
			bzero(buffer, sizeof(buffer));
			printf("Message from UDP client: ");
			n = recvfrom(udpfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
            sleep(1);
			puts(buffer);
			sendto(udpfd, (const char*)message, sizeof(buffer), 0,
				(struct sockaddr*)&cliaddr, sizeof(cliaddr));
		}

		if(FD_ISSET(stdinfd, &rset))
		{
			fgets(input_str, 6, stdin);
			input_str[strlen(input_str) - 1] = '\0'; 
		
			if(!strcmp(input_str, "quit"))
			{
				puts("end of process");
				break;
			}
			else if(!strcmp(input_str,"ping"))
			{
				printf("Pong\n");
			}
		}
	}
    close(listenfd);
    close(connfd);
}
/******************************************************************************/
static int max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}
/******************************************************************************/