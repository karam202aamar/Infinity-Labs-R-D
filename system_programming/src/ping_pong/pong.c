/*******************************************************************************
 * Project: signals - ex2 - pong
 * Date: 13/11/2022
 * Name: karam aamar
 * Reviewer: 
 * Version: 1.0
*******************************************************************************/
#include <stdio.h>	/*pritf, perror*/
#include <signal.h> /*sigaction*/
#include <unistd.h> /*pid*/
/******************************************************************************/
# define GREEN        "\x1b[32m"
# define RESET        "\x1b[0m"
# define BLUE         "\x1b[34m"
/******************************************************************************/
int pong();
static void pongIMP();
/******************************************************************************/
int main()
{
    pong();
    return 0;
}
/******************************************************************************/
int pong()
{
    pid_t fork_return = 0;
	char *args[] = {NULL, NULL};
    struct sigaction pong;
    pong.sa_handler = pongIMP;
    sigaction(SIGUSR1, &pong, NULL);
    
    args[0] = "./ping";

    fork_return = fork();

    /*if we are in the child*/
    while(!fork_return)
    {
        /*use exec*/
        execvp(args[0],args);
    }
    while(fork_return > 0)
    {
        /* send the signal to the child (fork_return has child pid) */
        kill(fork_return, SIGUSR2);
        puts(GREEN"parent");
        pause();
    }
    return 0;
}
/******************************************************************************/
static void pongIMP()
{
    /* print ping action */
    printf(GREEN"pong\n");
}
/******************************************************************************/