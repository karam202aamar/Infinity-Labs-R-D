
/********************************quest 1 working edition**********************/
#include <stdio.h> /* fprintf, fopen, fclose */
#include <sys/types.h> /* mkfifo */
#include <sys/stat.h> /* mkfifo */
#include <fcntl.h> /* open, close */
#include <string.h> /* strlen */
#include <unistd.h>
/*******************************************************************************
 * Project: PIC Q2
 * Date: 18/01/2023
 * Name: karam aamar
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <stdio.h> /* fprintf, fopen, fclose */
#include <sys/types.h> /* mkfifo */
#include <sys/stat.h> /* mkfifo */
#include <fcntl.h> /* open, close */
#include <string.h> /* strlen */
#include <unistd.h>
/******************************************************************************/
int main()
{
    int fd_ch[2];
    int fd_par[2];
    /*fd[0] - read*/
    /*fd[1] - write*/
    int id;
    char buff[5];
    char* ping_str = "ping";
    char* pong_str = "pong";

    /*use pipe sys call to communicate*/
    if(-1 == pipe(fd_ch))
    {
        printf("failed to create the pipe");
        return 1;
    }
    if(-1 == pipe(fd_par))
    {
        printf("failed to create the pipe");
        return 1;
    }
    /*create a child*/
    id = fork();
    /*infinite loop*/
    while(1)
    {
        /*if it's a child process*/
        if(0 == id)
        {   
            /*write into parent pipe*/
            write(fd_par[1], ping_str, 5);
            /*read child pipe*/
            read(fd_ch[0], buff, 5);
            printf("%s\n",buff);
            memcpy(buff, "null", 5);
        }
        else/*if parent process*/
        {
            /*read parent pipe*/
            read(fd_par[0], buff, 5);
            /*write into child pipe*/
            write(fd_ch[1], pong_str, 5);
            printf("%s\n",buff);
            memcpy(buff, "null", 5);
        }
    }
    return 0;
}
/******************************************************************************/
/******************************************************************************/
int main()
{
    int fd[2];
    /*fd[0] - read*/
    /*fd[1] - write*/
    int id;
    char buff[5];
    char* ping_str = "ping";
    char* pong_str = "pong";

    /*use pipe sys call to communicate*/
    if(-1 == pipe(fd))
    {
        printf("failed to create the pipe");
        return 1;
    }
    /*create a child*/
    id = fork();
    /*infinite loop*/
    while(1)
    {
        /*if it's a child process*/
        if(0 == id)
        {   
            /*there is no read here so close*/
            close(fd[0]);
            /*write ping to the pipe*/
            write(fd[1], ping_str, 5);
            /* printf("ping\n"); */
            /*close it*/
            close(fd[1]);
            
        }
        else/*if parent process*/
        {
            close(fd[1]);
            /*read it into buffer*/
            read(fd[0], buff, 5);
            printf("%s - buff here\n", buff);
            if(0 == strcmp(buff,ping_str))
            {
                printf("pong\n");
            }
            /* memcpy(buff, "null", 5); */
            
            close(fd[0]);
            
            /*  */
        }
    }
    
    return 0;
}
/******************************************************************************/