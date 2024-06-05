/******************************************************************************/
#include <semaphore.h>
#include <sys/sem.h>      
#include <pthread.h>    
#include <unistd.h>
#include <stdio.h>  
#include <fcntl.h> 
#include <stdlib.h>
/******************************************************************************/
#include "cbuf.h"
/******************************************************************************/
static void* ProdIMP(void* ptr_cbuf_MT);
static void* ConsIMP(void* ptr_cbuf_MT);
/******************************************************************************/
typedef struct CbufMT
{
    pthread_mutex_t mutex;
    sem_t sem_producer;
    sem_t sem_consumer;
    cbuf_ty *cbuff;

}CbufMT_ty;

int value_counter = 0;
/******************************************************************************/
enum{INIT = 0, NUM_OF_THREADS = 5};
/******************************************************************************/
int main()
{
    int i = 0;
    
    CbufMT_ty cbuf_MT;
    
    /*create threads*/
    pthread_t consumer_th[NUM_OF_THREADS] = {INIT};
    pthread_t producer_th[NUM_OF_THREADS] = {INIT};

    cbuf_MT.cbuff = CbufCreate(10 * sizeof(void*));

    /*initialize mutex & semaphores*/
    if(pthread_mutex_init(&cbuf_MT.mutex, NULL))
    {
        fputs("failed to init the mutex \n", stderr);
    }
    if(sem_init(&cbuf_MT.sem_producer, 0, 5))
    {
        fputs("failed to init sem_producer semaphore\n", stderr);
    }
    if(sem_init(&cbuf_MT.sem_consumer, 0, 0))
    {
        fputs("failed to init sem_consumer semaphore\n", stderr);
    }
    
    /*loop - create threads and join*/
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if(pthread_create(producer_th + i, NULL, &ProdIMP, &cbuf_MT))
        {
            fputs("failed to create producer threads\n", stderr);
        }
        if(pthread_create(consumer_th + i, NULL, &ConsIMP, &cbuf_MT))
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
    if (pthread_mutex_destroy(&cbuf_MT.mutex))
    {
        fputs("failed to destroy the mutex\n", stderr);
    }
    if (sem_destroy(&cbuf_MT.sem_consumer))
    {
        fputs("failed to destroy sem_ex4_cons semaphore\n", stderr);
    } 
    if (sem_destroy(&cbuf_MT.sem_producer))
    {
        fputs("failed to destroy sem_ex4_prod semaphore\n", stderr);
    }
    CbufDestroy(cbuf_MT.cbuff);

    return 0;
}
/******************************************************************************/
static void* ProdIMP(void* ptr_cbuf_MT)
{
    int *num = 0;
    CbufMT_ty* cbuf_MT = (CbufMT_ty*)ptr_cbuf_MT;

    while(1)
    {
        num = (int *)malloc(sizeof(int));
        *num = value_counter;
        
        if(sem_wait(&cbuf_MT->sem_producer))
        {
            fputs("failed to wait for sem_producer semaphore\n", stderr);
        }

        if(pthread_mutex_lock(&cbuf_MT->mutex))
        {
            fputs("failed to lock mutex_ex5 mutex \n", stderr);
        }
        CbufWrite(cbuf_MT->cbuff, &num, sizeof(void*));

        ++value_counter; 

        if(pthread_mutex_unlock(&cbuf_MT->mutex))
        {
            fputs("failed to unlock mutex_ex5 mutex\n", stderr);
        }  

        if(sem_post(&cbuf_MT->sem_consumer))
        {
            fputs("failed to post sem_consumer semaphore\n", stderr);
        }
    }
    return NULL;
}
/******************************************************************************/
static void* ConsIMP(void* ptr_cbuf_MT)
{
    int *num = 0;
    CbufMT_ty* cbuf_MT = (CbufMT_ty*)ptr_cbuf_MT;
    
    while(1)
    {
        if(sem_wait(&cbuf_MT->sem_consumer))
        {
            fputs("failed\n", stderr);
        }
        
        if(pthread_mutex_lock(&cbuf_MT->mutex))
        {
            fputs("failed\n", stderr);
        }

        CbufRead(cbuf_MT->cbuff, &num, sizeof(void*));
        sleep(0);
        printf("the values of reading from buffer : %d\n", *num);

        if (pthread_mutex_unlock(&cbuf_MT->mutex))
        {
            fputs("failed\n", stderr);
        }  
        if (sem_post(&cbuf_MT->sem_producer))
        {
            fputs("failed\n", stderr);
        }
        free(num);
    }
    return NULL;
}
/******************************************************************************/