/*******************************************************************************
 * Project: watchdog project
 * Date: 01/12/22
 * Name: Karam Aamar
 * Reviewer: IDAN
 * Version: 1.0 
*******************************************************************************/
/******************************************************************************/
#include <semaphore.h>
#include <sys/sem.h>      
#include <pthread.h>    
#include <unistd.h>
#include <stdio.h>  
#include <fcntl.h> 
#include <stdlib.h>
#include <assert.h>
#include <signal.h> 
#include <stdatomic.h>  
#include <string.h>
/*******************************header includes********************************/
#include "watch_dog.h"
#include "scheduler.h"
/***********************************defines************************************/
#define WD_PID "WD_PID"
#define WD_PATH "wdm_exe"
/*************************************enums************************************/
enum{INIT};
enum{DEAD, ALIVE};
enum{NOT_READY, READY};
enum{FAILURE = 1};
enum{WHO, MAIN_PROG, MAIN_PROG_PATH, DOG, DOG_PATH};
/********************************global variables******************************/
static pthread_t glob_dog_tid = INIT;
volatile atomic_int glob_ready_state = INIT;
static volatile atomic_int g_tolerance_count = INIT;
static volatile atomic_int g_dog_no_pulse = INIT;
/***********************************struct*************************************/
typedef struct WDP
{
    time_t time_interval;
    size_t tolerance_count;
    char **argv; 
}WDP_ty; /*WATCH DOG PROPERITIES*/
/****************************useful/helper functions***************************/
static void SigUsr1();
static void SigUsr2();
static int ForkIMP(void* watch_dog_info);
static void RunWD(WDP_ty* watch_dog_info);
static int TaskFuncImp(void* watch_dog_info);
static void* WatchDogThread(void* watch_dog_info);
/******************************************************************************/
int MakeMeImMortal(time_t interval, size_t tolerance_count, char *argv[])
{
    WDP_ty* watch_dog_info = NULL;

    assert(argv);

    /*dynamicall allocate watch_dog_properities*/
    watch_dog_info = (WDP_ty*)malloc(sizeof(WDP_ty));

    /*check allocation*/
    if(NULL == watch_dog_info)
    {
        /*error message*/
        fputs("failed \n", stderr);
    }

    /*init WATCH DOG PROPERITIES*/
    watch_dog_info -> time_interval = interval;
    watch_dog_info -> tolerance_count = tolerance_count;
    watch_dog_info -> argv = argv;
    
    /*create a thread for the WD - that copy the watch_dog_info & RUN watch dog*/
    if(pthread_create(&glob_dog_tid, NULL, WatchDogThread, (void*)watch_dog_info))
    {
        fputs("failed\n", stderr);
        return FAILURE;
    }

    pthread_join(glob_dog_tid, NULL);

    /*check when the program ready to run*/
    while(0 == atomic_load(&glob_ready_state))
    {
        /*fetch another process baby*/
        sleep(0);
    }
    return SUCCESS;
}
/******************************************************************************/
static void* WatchDogThread(void* watch_dog_info)
{
    RunWD((WDP_ty*)watch_dog_info);

    return NULL;
}
/******************************************************************************/
static void RunWD(WDP_ty* watch_dog_info)
{
    scheduler_ty* scheduler = NULL;
    ilrd_uid_ty task_id = {0};
    pid_t process_id = 0;

    sigset_t blocked_signals;

    struct sigaction sig_usr1;
    struct sigaction sig_usr2;

    sig_usr1.sa_handler = SigUsr1;
    sig_usr2.sa_handler = SigUsr2;

    sigaction(SIGUSR1, &sig_usr1, NULL);
    sigaction(SIGUSR2, &sig_usr2, NULL);

    /*init signals*/
    if(sigemptyset(&blocked_signals))
    {
        /*error message*/
        fputs("failed \n", stderr);
    }
    /*add relevant signal*/
    if(sigaddset(&blocked_signals, SIGUSR1))
    {
        /*error message*/
        fputs("failed \n", stderr);
    }
    if(sigaddset(&blocked_signals, SIGUSR2))
    {
        /*error message*/
        fputs("failed \n", stderr);
    }
    if(sigprocmask(SIG_BLOCK, &blocked_signals, NULL))
    {
        /*error message*/
        fputs("failed \n", stderr);
    }

    scheduler = SchedulerCreate();
    task_id = SchedulerAddTask(scheduler, watch_dog_info->time_interval, 
                                                TaskFuncImp, watch_dog_info);

    puts("watching the process");

    if(UIDIsSame(task_id, UIDBadUID))
    {
        /*error message*/
        fputs("failed \n", stderr);
    }
    
    SchedulerRun(scheduler);

    SchedulerDestroy(scheduler);
}
/******************************************************************************/
static void SigUsr1()
{
    if (atomic_load(&glob_ready_state) == 0)
    {
        atomic_fetch_add(&glob_ready_state, 1);
    }
    atomic_fetch_and(&g_tolerance_count, 0);
}
/******************************************************************************/
static void SigUsr2()
{
    atomic_fetch_add(&g_dog_no_pulse, 1);
}
/******************************************************************************/
static int TaskFuncImp(void* watch_dog_info)
{
    char *ret = NULL;
    char *recove_pid = getenv(WD_PID);
    char** argv = ((WDP_ty*)watch_dog_info)->argv;
    pid_t process_id = 0;
    size_t tolerance_count = ((WDP_ty*)watch_dog_info)->tolerance_count;
    
    if(atomic_load(&g_dog_no_pulse)> 0)
    {
        kill(process_id, SIGUSR2);

        return SUCCESS;
    }
    if(atomic_load(&g_dog_no_pulse) > tolerance_count)
    {
        atomic_fetch_and(&g_tolerance_count, 0);
        atomic_fetch_and(&glob_ready_state, 0);
        ForkIMP(watch_dog_info);
    }
    atomic_fetch_add(&g_tolerance_count, 1);
    ret = getenv(WD_PID);

    if (ret) 
    {
        process_id = atoi(ret);
    }
    kill(process_id, SIGUSR1);

    return 1;
}
/******************************************************************************/
static int ForkIMP(void* watch_dog_info)
{
    int status = INIT;
    pid_t child_pid = INIT;
    WDP_ty* wd_info = (WDP_ty*) watch_dog_info;

    char loc_tolerance_count[10] = {0};
    char loc_time_interval[10] = {0};
    char loc_env_pid[10] = {0};
    
    sprintf(loc_tolerance_count, "%ld", wd_info->tolerance_count);
    sprintf(loc_tolerance_count, "%ld", wd_info->tolerance_count);

    if(NULL == getenv(WD_PID))
    {
        sprintf(loc_env_pid, "%d", getpid());
        if(setenv(WD_PID, loc_env_pid, 1))
        {
            fputs("failed setenv\n", stderr);
        }
        child_pid = fork();
        
        if(0 == child_pid)
        {
            if(-1 == execl(WD_PATH, WD_PATH, loc_tolerance_count, 
                                loc_time_interval, wd_info->argv[1], NULL))
            {
                /*error message*/
                fputs("failed \n", stderr);
            }
        }
        sprintf(loc_env_pid, "%d", child_pid);
        setenv(WD_PID, loc_env_pid, 1);
    }
    else
    {
        if(!strcmp(wd_info->argv[0], WD_PATH))
        {
            unsetenv(WD_PID);
            execl(wd_info->argv[3], wd_info->argv[3], wd_info->argv[3], NULL);
        }
        else
        {
            execl(WD_PATH, WD_PATH, loc_tolerance_count, loc_time_interval,
                                                    wd_info->argv[0], NULL);
        }
    }
    while(!atomic_load(&glob_ready_state))
    {
        sleep(0);
    }
    return SUCCESS;
}
/******************************************************************************/
void LetMeDie()
{
    pid_t process_id = (pid_t)atoi(getenv(WD_PID));
    kill(process_id, SIGUSR2);
    pthread_join(glob_dog_tid, NULL);
}
/******************************************************************************/
#if 0
    /*init argv InitEnvIMP(argv)*/
    if(InitEnvIMP(argv))
    {
        fputs("failed to init env\n", stderr);

        return FAILURE;
    }
    /*use getenv to get the pid of the dog & status*/
    if(getenv("doggo_pid"))
    {
        glob_dog_pid = atoi(getenv("dog_pid"));
        glob_dog_state = ALIVE;
    }
    /*create a thread & call the function that run the dog - DogRun*/
    if(pthread_create(&glob_dog_tid, NULL, CallWatchDog, NULL))
    {
        fputs("failed\n", stderr);
        return FAILURE;
    }
    return SUCCESS;
    #endif