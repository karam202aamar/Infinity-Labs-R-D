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
#include "cbuf.h"
/******************************************************************************/
static void Ex1IMP();
static void* Prod1IMP();
static void* Cons1IMP();


static void Ex2IMP();
static void* Prod2IMP(void* linked_list);
static void* Cons2IMP(void* linked_list);
pthread_mutex_t mutex_ex2;
pthread_cond_t condition;
int state_var;

static void Ex3IMP();
static void* Prod3IMP(void* linked_list);
static void* Cons3IMP(void* linked_list);
pthread_mutex_t mutex_ex3;
sem_t sem_ex3;

static void Ex4IMP();
static void* Prod4IMP(void* void_cbuff);
static void* Cons4IMP(void* void_cbuff);
pthread_mutex_t mutex_ex4;
sem_t sem_ex4_prod;
sem_t sem_ex4_cons;

static void Ex5IMP();
static void* Prod5IMP(void* void_cbuff);
static void* Cons5IMP(void* void_cbuff);
pthread_mutex_t mutex_ex5_prod;
pthread_mutex_t mutex_ex5_cons;
sem_t sem_ex5_prod;
sem_t sem_ex5_cons;
/******************************************************************************/
enum{INIT = 0, ONE_VAL, DESIRED_VAL, NUM_OF_THREADS = 5, SECTIONS = 500};
enum{PROD_PERMITTED = 0, CONS_PERMITTED = 1};
/******************************************************************************/
int counter = 0;
int is_avai_key = 0;
int arr_ex1[500] = {0};

int values[] = {0, 1, 2, 3, 4};
int value_counter = 0;
/******************************************************************************/
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
    if(3 == ex_to_run)
    {
        Ex3IMP();
    }
    if(4 == ex_to_run)
    {
        Ex4IMP();
    }
    if(5 == ex_to_run)
    {
        Ex5IMP();
    }
    return 0;
}
/******************************************************************************/
static void Ex1IMP()
{
    int i = INIT;
    /* define threads for consumer & producer */
    pthread_t consumer_th = INIT;
    pthread_t producer_th = INIT;

    if(pthread_create(&consumer_th, NULL, &Cons1IMP, NULL))
    {
        fputs("failed to create the thread\n", stderr);
    }

    if (pthread_create(&producer_th, NULL, &Prod1IMP, NULL))
    {
       fputs("failed to create the thread\n", stderr);
    }

    pthread_join(consumer_th, NULL);
    pthread_join(producer_th, NULL);
    
    for(i = INIT; i < SECTIONS; ++i)
    {
        if(DESIRED_VAL != arr_ex1[i])
        {
            printf("failed at %d\n",i);
        }
    }
}
/******************************************************************************/
static void* Prod1IMP()
{
    while (counter < 500)
    {
        if (!is_avai_key)
        {
            arr_ex1[counter] += ONE_VAL;
            is_avai_key = CONS_PERMITTED;   
        }
    }
    return NULL;
}
/******************************************************************************/
static void* Cons1IMP()
{
    while (counter < 500)
    {
        if (is_avai_key)
        {
            arr_ex1[counter] += ONE_VAL;
            ++counter;
            is_avai_key = PROD_PERMITTED;
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
    slist_ty *linked_list = SListCreate();
    /*check allocation*/
    if(NULL == linked_list)
    {
        fputs("failed to create linked list\n", stderr);
    }

    /*initialize mutex*/
    pthread_mutex_init(&mutex_ex2, NULL);

    /*loop - create threads and join*/
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if(pthread_create(consumer_th + i, NULL, &Cons2IMP, (void*)linked_list))
        {
            fputs("failed to create the thread\n", stderr);
        }
        if(pthread_create(producer_th + i, NULL, &Prod2IMP, (void*)linked_list))
        {
            fputs("failed to create the thread\n", stderr);
        }
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(consumer_th[i], NULL);
        pthread_join(producer_th[i], NULL);
    }
    if (pthread_mutex_destroy(&mutex_ex2))
    {
        fputs("failed to destroy the mutex\n", stderr);
    }
    SListDestroy(linked_list);
}
/******************************************************************************/
static void* Prod2IMP(void* linked_list)
{   
    slist_ty* list = (slist_ty*)linked_list;
    
    if(pthread_mutex_lock(&mutex_ex2))
    {
        fputs("failed to lock the mmutex\n", stderr);
    }

    if (!SListInsert(SListBegin(list), &values[value_counter]))
    {
        fputs("failed insert in the linked list\n", stderr);
    }

    printf("producer: %d\n", values[value_counter]);
    pthread_cond_signal(&condition);

    if (pthread_mutex_unlock(&mutex_ex2))
    {
        fputs("failed to unlock mutex_ex2\n", stderr);
    }    

    ++value_counter;      

    return NULL;
}
/******************************************************************************/
static void* Cons2IMP(void* linked_list)
{
    slist_ty *list = (slist_ty *)linked_list;
    
    if (pthread_mutex_lock(&mutex_ex2))
    {
       fputs("failed to lock mutex_ex2\n", stderr);
    }

    while (0 == SListCount(list))
    {
        pthread_cond_wait(&condition, &mutex_ex2);
    }

    printf("consumer: %d\n", *(int *)SListGetData((SListBegin(list))));
    SListRemove(SListBegin(list));

    if (pthread_mutex_unlock(&mutex_ex2))
    {
        fputs("failed to unlock mutex_ex2\n", stderr);
    }  

    printf("thread  ID: %ld\n", pthread_self());
    return NULL;
}
/******************************************************************************/
static void Ex3IMP()
{
    int i;

    /*create threads*/
    pthread_t consumer_th[NUM_OF_THREADS] = {0};
    pthread_t producer_th[NUM_OF_THREADS] = {0};

    /*create linked list*/
    slist_ty *linked_list = SListCreate();

    sem_init(&sem_ex3, 0, 0);

    /*check allocation*/
    if(NULL == linked_list)
    {
        fputs("failed to allocate linked list\n", stderr);
    }

    /*initialize mutex*/
    pthread_mutex_init(&mutex_ex3, NULL);

    /*loop - create threads and join*/
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if(pthread_create(producer_th + i, NULL, &Prod3IMP, (void*)linked_list))
        {
            fputs("failed to create producer threads\n", stderr);
        }
        if(pthread_create(consumer_th + i, NULL, &Cons3IMP, (void*)linked_list))
        {
            fputs("failed to create consumer threads\n", stderr);
        }
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(consumer_th[i], NULL);
        pthread_join(producer_th[i], NULL);
    }
    if (pthread_mutex_destroy(&mutex_ex3))
    {
        fputs("failed to destroy mutex_ex3\n", stderr);
    }
    SListDestroy(linked_list);
}
/******************************************************************************/
static void* Prod3IMP(void* linked_list)
{   
    slist_ty* list = (slist_ty*)linked_list;
    
    if(pthread_mutex_lock(&mutex_ex3))
    {
        fputs("failed to lock mutex_ex3\n", stderr);
    }

    if (!SListInsert(SListBegin(list), &values[value_counter]))
    {
        fputs("failed insert in the linked list\n", stderr);
    }

    if (pthread_mutex_unlock(&mutex_ex3))
    {
        fputs("failed to unlock mutex_ex3\n", stderr);
    }  

    if (sem_post(&sem_ex3))
    {
        fputs("failed to post semaphore\n", stderr);
    }   
    printf("producer: %d\n", values[value_counter]);
    
    ++value_counter;      

    return NULL;
}
/******************************************************************************/
static void* Cons3IMP(void* linked_list)
{
    slist_ty *list = (slist_ty *)linked_list;
    
    if (sem_wait(&sem_ex3))
    {
        fputs("failed to wait\n", stderr);
    }

    if (pthread_mutex_lock(&mutex_ex3))
    {
       fputs("failed to lock mutex_ex3\n", stderr);
    }
    
    printf("consumer: %d\n", *(int *)SListGetData((SListBegin(list))));
    printf("thread  ID: %ld\n", pthread_self());
    SListRemove(SListBegin(list));
    
    if (pthread_mutex_unlock(&mutex_ex3))
    {
        fputs("failed to unlock mutex_ex3\n", stderr);
    }  

    return NULL;
}
/******************************************************************************/
static void Ex4IMP()
{
    int i = 0;

    /*create threads*/
    pthread_t consumer_th[NUM_OF_THREADS] = {0};
    pthread_t producer_th[NUM_OF_THREADS] = {0};

    /*create linked list*/
    cbuf_ty *cbuff = CbufCreate(NUM_OF_THREADS * sizeof(void*));
    
    /*check allocation*/
    if(NULL == cbuff)
    {
        fputs("failed\n", stderr);
    }

    /*initialize mutex & semaphores*/
    if(pthread_mutex_init(&mutex_ex4, NULL))
    {
        fputs("failed to init mutex_ex4 mutex \n", stderr);
    }

    if(sem_init(&sem_ex4_prod, 0, 5))
    {
        fputs("failed to init sem_ex4_prod semaphore\n", stderr);
    }

    if(sem_init(&sem_ex4_cons, 0, 0))
    {
        fputs("failed to init sem_ex4_cons semaphore\n", stderr);
    }
    
    /*loop - create threads and join*/
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if(pthread_create(producer_th + i, NULL, &Prod4IMP, (void*)cbuff))
        {
            fputs("failed to create producer threads\n", stderr);
        }
        if(pthread_create(consumer_th + i, NULL, &Cons4IMP, (void*)cbuff))
        {
            fputs("failed to create consumer threads\n", stderr);
        }
    }
    
    /*join the threads*/
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(consumer_th[i], NULL);
        pthread_join(producer_th[i], NULL);
    }
    
    /*destroy the semaphores & mutex*/
    if (pthread_mutex_destroy(&mutex_ex4))
    {
        fputs("failed to destroy the mutex\n", stderr);
    }
    if (sem_destroy(&sem_ex4_cons))
    {
        fputs("failed to destroy sem_ex4_cons semaphore\n", stderr);
    } 
    if (sem_destroy(&sem_ex4_prod))
    {
        fputs("failed to destroy sem_ex4_prod semaphore\n", stderr);
    }
    CbufDestroy(cbuff);
}
/******************************************************************************/
static void* Prod4IMP(void* void_cbuff)
{   
    int *num = 0;
    cbuf_ty* cbuff = (cbuf_ty*)void_cbuff;

    while(1)
    {
        num = (int *)malloc(sizeof(int));
        *num = value_counter;
        
        if(sem_wait(&sem_ex4_prod))
        {
            fputs("failed to wait for sem_ex4_prod semaphore\n", stderr);
        }

        if(pthread_mutex_lock(&mutex_ex4))
        {
            fputs("failed to lock mutex_ex4 mutex \n", stderr);
        }
        CbufWrite(cbuff, &num, sizeof(void*));

        ++value_counter; 

        if(pthread_mutex_unlock(&mutex_ex4))
        {
            fputs("failed to unlock mutex_ex4 mutex\n", stderr);
        }  

        if(sem_post(&sem_ex4_cons))
        {
            fputs("failed to post sem_ex4_cons semaphore\n", stderr);
        }
    }
    return NULL;
}
/******************************************************************************/
static void* Cons4IMP(void* void_cbuff)
{
    int *num = 0;
    cbuf_ty* cbuff = (cbuf_ty*)void_cbuff;
    
    while(1)
    {
        if(sem_wait(&sem_ex4_cons))
        {
            fputs("failed\n", stderr);
        }
        
        if(pthread_mutex_lock(&mutex_ex4))
        {
            fputs("failed\n", stderr);
        }

        CbufRead(cbuff, &num, sizeof(void*));

        if (pthread_mutex_unlock(&mutex_ex4))
        {
            fputs("failed\n", stderr);
        }  
        if (sem_post(&sem_ex4_prod))
        {
            fputs("failed\n", stderr);
        }
        printf("the values are : %d\n", *num);
        free(num);
    }

    return NULL;
}
/******************************************************************************/
static void Ex5IMP()
{
    int i = 0;

    /*create threads*/
    pthread_t consumer_th[NUM_OF_THREADS] = {0};
    pthread_t producer_th[NUM_OF_THREADS] = {0};

    /*create linked list*/
    cbuf_ty *cbuff = CbufCreate(NUM_OF_THREADS * sizeof(void*));
    
    /*check allocation*/
    if(NULL == cbuff)
    {
        fputs("failed\n", stderr);
    }

    /*initialize mutex & semaphores*/
    if(pthread_mutex_init(&mutex_ex5_prod, NULL))
    {
        fputs("failed to init mutex_ex5 mutex \n", stderr);
    }
    if(pthread_mutex_init(&mutex_ex5_cons, NULL))
    {
        fputs("failed to init mutex_ex5 mutex \n", stderr);
    }
    if(sem_init(&sem_ex5_prod, 0, 5))
    {
        fputs("failed to init sem_ex5_prod semaphore\n", stderr);
    }
    if(sem_init(&sem_ex5_cons, 0, 0))
    {
        fputs("failed to init sem_ex5_cons semaphore\n", stderr);
    }
    
    /*loop - create threads and join*/
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if(pthread_create(producer_th + i, NULL, &Prod5IMP, (void*)cbuff))
        {
            fputs("failed to create producer threads\n", stderr);
        }
        if(pthread_create(consumer_th + i, NULL, &Cons5IMP, (void*)cbuff))
        {
            fputs("failed to create consumer threads\n", stderr);
        }
    }
    
    /*join the threads*/
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(consumer_th[i], NULL);
        pthread_join(producer_th[i], NULL);
    }
    
    /*destroy the semaphores & mutex*/
    if (pthread_mutex_destroy(&mutex_ex5_prod))
    {
        fputs("failed to destroy the mutex\n", stderr);
    }
    if (pthread_mutex_destroy(&mutex_ex5_cons))
    {
        fputs("failed to destroy the mutex\n", stderr);
    }
    if (sem_destroy(&sem_ex5_cons))
    {
        fputs("failed to destroy sem_ex4_cons semaphore\n", stderr);
    } 
    if (sem_destroy(&sem_ex5_prod))
    {
        fputs("failed to destroy sem_ex4_prod semaphore\n", stderr);
    }
    CbufDestroy(cbuff);
}
/******************************************************************************/
static void* Prod5IMP(void* void_cbuff)
{
    int *num = 0;
    cbuf_ty* cbuff = (cbuf_ty*)void_cbuff;

    while(1)
    {
        num = (int *)malloc(sizeof(int));
        *num = value_counter;
        
        if(sem_wait(&sem_ex5_prod))
        {
            fputs("failed to wait for sem_ex5_prod semaphore\n", stderr);
        }

        if(pthread_mutex_lock(&mutex_ex5_prod))
        {
            fputs("failed to lock mutex_ex5 mutex \n", stderr);
        }
        CbufWrite(cbuff, &num, sizeof(void*));

        ++value_counter; 

        if(pthread_mutex_unlock(&mutex_ex5_prod))
        {
            fputs("failed to unlock mutex_ex5 mutex\n", stderr);
        }  

        if(sem_post(&sem_ex5_cons))
        {
            fputs("failed to post sem_ex5_cons semaphore\n", stderr);
        }
    }
    return NULL;
}
/******************************************************************************/
static void* Cons5IMP(void* void_cbuff)
{
    int *num = 0;
    cbuf_ty* cbuff = (cbuf_ty*)void_cbuff;
    
    while(1)
    {
        if(sem_wait(&sem_ex5_cons))
        {
            fputs("failed\n", stderr);
        }
        
        if(pthread_mutex_lock(&mutex_ex5_cons))
        {
            fputs("failed\n", stderr);
        }

        CbufRead(cbuff, &num, sizeof(void*));
        printf("the values are : %d\n", *num);

        if (pthread_mutex_unlock(&mutex_ex5_cons))
        {
            fputs("failed\n", stderr);
        }  
        if (sem_post(&sem_ex5_prod))
        {
            fputs("failed\n", stderr);
        }
        free(num);
    }
    return NULL;
}
/******************************************************************************/














