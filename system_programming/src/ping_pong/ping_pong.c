/*******************************************************************************
 * Project: signals
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
static void pingIMP();
static void pongIMP();
/******************************************************************************/
int main()
{
    pid_t fork_return = 0;

    /* declare the structs we have */
    struct sigaction ping;
    struct sigaction pong;

    /* set handling functions */
    ping.sa_handler = pingIMP;
    pong.sa_handler = pongIMP;

    /* set sig action functions for each signal */
    sigaction(SIGUSR1, &pong, NULL);
    sigaction(SIGUSR2, &ping, NULL);

    /* use fork to create process */
    fork_return = fork();

    /* check if fork failed */
    if(-1 == fork_return)
    {
        perror("perror");
        return 0;
    }

    /* child process */
    while(0 == (fork_return))
    {   
        /* print our position */
        sleep(1);
        puts(BLUE"child");
       
        /* send a signal */
        kill(getppid(), SIGUSR2);

        pause();
    }
    /* parent process */
    while(0 < fork_return)
    {
        wait();

        /* print our position */
        sleep(1);
        puts(GREEN"parent");

        /* send the signal to the child (fork_return has child pid) */
        kill(fork_return, SIGUSR1);
    }
    
    return 0;
}
/******************************************************************************/
static void pongIMP()
{
    sleep(1);
    /* print ping action */
    printf(GREEN"pong\n");
}
/******************************************************************************/
static void pingIMP()
{
    sleep(1);
    /* print ping action */
    printf(BLUE"ping\n");
}
/******************************************************************************/