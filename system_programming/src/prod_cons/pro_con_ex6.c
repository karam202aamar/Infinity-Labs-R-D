/******************************************************************************/
#include <signal.h>     
#include <stdio.h>      
#include <time.h>           
#include <pthread.h>    
#include <unistd.h>     
#include <sys/types.h>  
#include <semaphore.h>  
#include <string.h>
/******************************************************************************/
static void *ConsumerIMP();
static void *ProducerIMP();
/******************************************************************************/
enum{MULTIPLE = 5};
/******************************************************************************/
typedef struct MessageRead
{
    sem_t semaphore;
    pthread_mutex_t mutex;
    pthread_cond_t conditional_var;
    
}MessageRead_ty;
/******************************************************************************/
int counter = 0;
char g_str[MULTIPLE] = {0};
MessageRead_ty message;
/******************************************************************************/
int main()
{
    pthread_t consumer[MULTIPLE] = {0}; 
    pthread_t producer = 0;
    int i = 0;

    counter = -1;

    if (sem_init(&message.semaphore, 0, 1))
    {
        fputs("failed\n", stderr);
    } 
    if (pthread_mutex_init(&message.mutex, NULL))
    {
        fputs("failed\n", stderr);
    }
    if (pthread_create(&producer, NULL, ProducerIMP, NULL))
    {
        fputs("failed\n", stderr);
    }
    for (i = 0; MULTIPLE > i; ++i)
    {
        if (pthread_create(&consumer[i], NULL, ConsumerIMP, NULL))
        {
            fputs("failed\n", stderr);
        }
    }

    sleep(2);
    pthread_join(producer, NULL);
    
    for (i = 0; MULTIPLE > i; ++i)
    {
        pthread_join(consumer[i], NULL);
    }
    if (sem_destroy(&message.semaphore))
    {
        fputs("failed\n", stderr);
    } 
    if (pthread_mutex_destroy(&message.mutex))
    {
        fputs("failed\n", stderr);
    }  
    if (pthread_cond_destroy(&message.conditional_var))
    {
        fputs("failed\n", stderr);
    }      

    return 0;
}
/******************************************************************************/
static void *ProducerIMP()
{
    int i = 0;
    /*create local string*/
    char local_str[MULTIPLE] = {'m', 'i', 'l', 'k', 'y'};
    
    /*loop*/
    while (MULTIPLE > counter)
    {
        /*decrement the semaphore key by NUM of threads*/
        for (i = 0; MULTIPLE > i; ++i)
        {
            /*wait (decrement key num)*/
            if (sem_wait(&message.semaphore))
            {
                fputs("failed\n", stderr);
            }   
        }
        ++counter;
        g_str[counter] = local_str[counter];    
        printf("producer: %c\n", g_str[counter]);

        /*free the threads*/
        if (pthread_cond_broadcast(&message.conditional_var))
        {
            fputs("failed\n", stderr);
        }           
        sleep(1);
    }

    return NULL;
}
/******************************************************************************/
static void *ConsumerIMP()
{
    char local_str[MULTIPLE] = {0};

    while (MULTIPLE > counter)
    {   
        /*lock the critical area*/
        if (pthread_mutex_lock(&message.mutex))
        {
            fputs("failed\n", stderr);
        }
        if (sem_post(&message.semaphore))
        {
            fputs("failed\n", stderr);
        }   
        /*wait here untill we get a broadcast for all*/
        if (pthread_cond_wait(&message.conditional_var, &message.mutex))
        {
            fputs("failed\n", stderr);
        }

        local_str[counter] = g_str[counter];
        printf("consumer: %c counter: %d thread id: %ld\n", 
                                   local_str[counter], counter, pthread_self()); 

        if (pthread_mutex_unlock(&message.mutex))
        {
            fputs("failed\n", stderr);
        }
    }    
    printf("the final string is: %s\n", local_str);
    return NULL;
}
/******************************************************************************/
/*solution which only one thread access the element */
#if 0
int main()
{
    pthread_t consumer[MULTIPLE] = {0}; 
    pthread_t producer = 0;
    int i = 0;

    if (sem_init(&message.semaphore, 0, 0))
    {
        fputs("failed\n", stderr);
    } 

    if (pthread_mutex_init(&message.mutex, NULL))
    {
        fputs("failed\n", stderr);
    }

    if (pthread_create(&producer, NULL, ProducerIMP, NULL))
    {
        fputs("failed\n", stderr);
    }

    for (i = 0; MULTIPLE > i; ++i)
    {
        if (pthread_create(&consumer[i], NULL, ConsumerIMP, NULL))
        {
            fputs("failed\n", stderr);
        }
    }

    sleep(1);

    pthread_join(producer, NULL);
    
    for (i = 0; MULTIPLE > i; ++i)
    {
        pthread_join(consumer[i], NULL);
    }

    if (sem_destroy(&message.semaphore))
    {
        fputs("failed\n", stderr);
    } 

    if (pthread_mutex_destroy(&message.mutex))
    {
        fputs("failed\n", stderr);
    }  

    if (pthread_cond_destroy(&message.conditional_var))
    {
        fputs("failed\n", stderr);
    }      

    return 0;
}
/******************************************************************************/
static void *ProducerIMP()
{   
    int i = 0; 
    int value = 0;
                       
    char local_str[6] = {'k', 'a', 'r', 'a', 'm', '\0'};

    if (pthread_mutex_lock(&message.mutex))
    {
        fputs("failed\n", stderr);
    } 
    
    while(value)
    {
        if (pthread_cond_wait(&message.conditional_var, &message.mutex))
        {
            fputs("failed\n", stderr);
        }
        sem_getvalue(&message.semaphore, &value);
    }

    strcpy(g_str, local_str);

    while(i < 5)
    {
        if (sem_post(&message.semaphore))
        {
            fputs("failed\n", stderr);
        }
        ++i;
    }

    if (pthread_mutex_unlock(&message.mutex))
    {
        fputs("failed\n", stderr);
    }
    return NULL;
}

/******************************************************************************/
static void *ConsumerIMP()
{
    char local_str[MULTIPLE] = {0};
    
    if (sem_wait(&message.semaphore))
    {
        fputs("failed\n", stderr);
    } 
      
    if (pthread_mutex_lock(&message.mutex))
    {
        fputs("failed\n", stderr);
    } 
    /* send signal */
    if (pthread_cond_signal(&message.conditional_var))
    {
        fputs("failed\n", stderr);
    }  

    local_str[counter] = g_str[counter];
    printf("cons: %c counter: %d \n", local_str[counter], counter); 
    ++counter;
    
    if (pthread_mutex_unlock(&message.mutex))
    {
        fputs("failed\n", stderr);
    }
        
    return NULL;
}
/******************************************************************************/
#endif
