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