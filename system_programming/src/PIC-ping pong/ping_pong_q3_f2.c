/*******************************************************************************
 * Project: PIC Q3 - process 2
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

int main()
{
    int fd1;

    /* FIFO file path */
    char * myfifo = "/tmp/myfifo";
    char* ping_str = "ping";
    char* pong_str = "pong";
    char buff[5] = {0};

    /*Creating the named file(FIFO)
      mkfifo(<pathname>,<permission>) */
    mkfifo(myfifo, 0666);

    while (1)
    {
        /* First open in read only and read */
        fd1 = open(myfifo,O_RDONLY);
        read(fd1, buff, 5);

        /* Print the read string and close */
        printf("%s\n", buff);
        close(fd1);

        /* Now open in write mode and write
         string taken from user. */
        fd1 = open(myfifo,O_WRONLY);
        write(fd1, pong_str, 5);
        close(fd1);
    }
    return 0;
}