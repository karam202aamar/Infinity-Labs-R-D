/*******************************************************************************
 * Project: 
 * Date: 22/11/2022
 * Name: karam aamar
 * Reviewer: ortal
 * Version: 1.0
*******************************************************************************/
#include <sys/types.h>      
#include <fcntl.h> 
#include <sys/stat.h>  
#include <string.h>         
#include <stdlib.h>
#include <stdio.h>          
#include <semaphore.h>      
#include <sys/sem.h>      
#include <pthread.h>    
#include <unistd.h>
/******************************************************************************/
#include "linked_list.h"
/******************************************************************************/
static void Ex1IMP();
static void* Prod1IMP();
static void* Cons1IMP();

static void Ex2IMP();
static void* Prod2IMP(void* linked_list);
static void* Cons2IMP(void* linked_list);
int values[] = {0, 1, 2, 3, 4};
int value_counter = 0;

/******************************************************************************/
enum{NUM_OF_THREADS = 5};
/******************************************************************************/
/*EX1 GLOBAL VARIABLE*/
int counter = 0;
int is_avai_key = 0;

/*EX2 GLOBAL VARIABLE*/
pthread_mutex_t mutex_ex2;

int main()
{
    int ex_to_run;

    puts("choose an exercise 1-6:");
    scanf("%d", &ex_to_run);

    if(1 == ex_to_run)
    {
        Ex1IMP();
    }
    if(2 == ex_to_run)
    {
        Ex2IMP();
    }
    return 0;
}
/******************************************************************************/
static void Ex1IMP()
{
    /* define threads for consumer & producer */
    pthread_t consumer_th = 0;
    pthread_t producer_th = 0;

    puts("output");

    if(pthread_create(&consumer_th, NULL, &Cons1IMP, NULL))
    {
        puts("failed to create");
    }

    if (pthread_create(&producer_th, NULL, &Prod1IMP, NULL))
    {
       puts("failed to create");
    }

    pthread_join(consumer_th, NULL);
    pthread_join(producer_th, NULL);
}
/******************************************************************************/
static void* Prod1IMP()
{
    while (counter < 5)
    {
        if (!is_avai_key)
        {
            is_avai_key = 1;
            ++counter;
            puts("1");
        }
    }
    return NULL;
}
/******************************************************************************/
static void* Cons1IMP()
{
    while (counter < 5)
    {
        sleep(1);
        if (is_avai_key)
        {
            is_avai_key = 0;
            puts("0");
        }
    }
    return NULL;
}
/******************************************************************************/
static void Ex2IMP()
{
    int i;

    /*create threads*/
    pthread_t consumer_th[NUM_OF_THREADS] = {0};
    pthread_t producer_th[NUM_OF_THREADS] = {0};

    /*create linked list*/
    slist_ty linked_list = SListCreate();
    /*check allocation*/
    if(NULL == linked_list)
    {
        perror("failed to allocate linked list");
    }

    /*initialize mutex*/
    pthread_mutex_init(&mutex_ex2, NULL);

    /*loop - create threads and join*/
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if(pthread_create(consumer_th + i, NULL, &Cons2IMP, (void*)linked_list))
        {
            perror("failed to create consumer threads");
        }
        if(pthread_create(producer_th + i, NULL, &Prod2IMP, (void*)linked_list))
        {
            perror("failed to create producer threads");
        }
    }
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(consumer_th[i], NULL);
        pthread_join(producer_th[i], NULL);
    }
    if (pthread_mutex_destroy(&mutex_ex2))
    {
        perror("failed to destroy mutex_ex2");
    }
}
/******************************************************************************/
static void* Prod2IMP(void* linked_list)
{   
    slist_ty* list = (slist_ty*)linked_list;
    /*lock*/
    if(pthread_mutex_lock(&mutex_ex2))
    {
        perror("failed to lock mutex_ex2");
    }

    printf("prod %d\n", g_i[g_counter]);

    if (SListInsert(SListBegin(list), &values[value_counter]))
    {
        perror("failed insert in the linked list");
    }

    if (pthread_mutex_unlock(&mutex_ex2))
    {
        perror("failed to unlock mutex_ex2");
    }  

    ++value_counter;      

    return NULL;
}
/******************************************************************************/
static void* Cons2IMP(void* linked_list)
{
    dlist_ty *list = (dlist_ty *)linked_list;

    if (pthread_mutex_lock(&mutex_ex2))
    {
       perror("failed to lock mutex_ex2");
    }

    while (0 != SListCount(list))
    {
        printf("value: %d\n", *(int *)SListGetData(SListRemove(SListBegin(list))));
    }

    if (pthread_mutex_unlock(&mutex_ex2))
    {
        perror("failed to unlock mutex_ex2");
    }  

    return NULL;
}
/******************************************************************************/



















