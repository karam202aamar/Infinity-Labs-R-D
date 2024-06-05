/*******************************************************************************
 * Project: 
 * Date: 17/11/22
 * Name: karam
 * Reviewer: 
 * Version: 1.0 
*******************************************************************************/
#define _POSIX_C_SOURCE 200809L 

#include <signal.h>         
#include <stdio.h>          
#include <sys/types.h>      
#include <unistd.h>         
#include <sys/wait.h>       
#include "utils.h"

int count = 0;

void PingIMP(int sig, siginfo_t *info, void *ucontext);
/******************************************************************************/
int main()
{
    int counter = 10;
    char *args[2];
    int exec_stat = 0;
    pid_t pid_fork = 0;

    struct sigaction sa_ping;

    sigemptyset(&sa_ping.sa_mask);
    sa_ping.sa_flags = SA_SIGINFO;

    sa_ping.sa_handler = PingIMP;
    sigaction(SIGUSR2, &sa_ping, NULL);

    while(counter)
    {
        pause();
        --counter;
    }

    return 0;    
}
/******************************************************************************/
void PingIMP(int sig, siginfo_t *info, void *ucontext)
{
    ++count;

    printf("Ping %d \n", count); 
    printf("pid: %d \n", info->si_pid);

    kill(info->si_pid, SIGUSR1);
}
/******************************************************************************/



