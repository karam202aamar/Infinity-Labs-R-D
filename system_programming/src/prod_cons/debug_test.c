#include <stdio.h>          
#include <pthread.h>    
#include <unistd.h>
/******************************************************************************/
static void* Prod1IMP();
static void* Cons1IMP();
/******************************************************************************/
int main()
{
    pthread_t consumer_th = 0;
    pthread_t producer_th = 0;

    pthread_create(&producer_th, NULL, &Prod1IMP, NULL);
    puts("hey");
    pthread_create(&consumer_th, NULL, &Cons1IMP, NULL);
    
    pthread_join(consumer_th, NULL);
    pthread_join(producer_th, NULL);

    return 0;
}
/******************************************************************************/
static void* Prod1IMP()
{   
    sleep(10);
    printf("producer thread the id %ld\n",pthread_self());
    return NULL;
}
/******************************************************************************/
static void* Cons1IMP()
{
    sleep(10);
    printf("consumer thread the id %ld\n",pthread_self());
    return NULL;
}
/******************************************************************************/