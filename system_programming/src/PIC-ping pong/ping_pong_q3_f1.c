/*******************************************************************************
 * Project: PIC Q3 - process 1
 * Date: 18/01/2023
 * Name: karam aamar
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
/******************************************************************************/
#define STR_LEN 5
/******************************************************************************/
int main()
{
    int fd;

    /*FIFO file path */
    char * myfifo = "/tmp/myfifo";
    char* ping_str = "ping";
    char* pong_str = "pong";
    char buff[STR_LEN];
    
    /*Creating the named file(FIFO)
      mkfifo(<pathname>, <permission>)*/
    mkfifo(myfifo, 0666);

    while (1)
    {
        /* Open FIFO for write only */
        fd = open(myfifo, O_WRONLY);

        write(fd, ping_str, 5);
        close(fd);

        /* Open FIFO for Read only */
        fd = open(myfifo, O_RDONLY);

        /* Read from FIFO */
        read(fd, buff, 5);

        /* Print the read message */
        printf("%s\n", buff);
        close(fd);
    }
    return 0;
}



