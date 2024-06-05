/*******************************************************************************
 * Project: signals - ex2 - ping
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
int ping();
static void pingIMP();
/******************************************************************************/
int main()
{
    ping();
    return 0; 
}
/******************************************************************************/
int ping()
{
    /* declare the structs we have */
    struct sigaction ping;
    /* set handling functions */
    ping.sa_handler = pingIMP;
    /* when we get SIG call pong fuction */
    sigaction(SIGUSR2, &ping, NULL);
    
    while(1)
    {
        pause();
        puts(BLUE"child");
        kill(getppid(), SIGUSR1);
    }
    return 0;
}
/******************************************************************************/
static void pingIMP()
{
    /* print ping action */
    printf(BLUE"ping\n");
}
/******************************************************************************/