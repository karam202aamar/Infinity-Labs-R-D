#include <semaphore.h>
#include <sys/sem.h>      
#include <pthread.h>    
#include <unistd.h>
#include <stdio.h>  
#include <fcntl.h> 
#include <stdlib.h>
#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>
 /*****************************************************************************/
atomic_int counter;
int cnt;
 /*****************************************************************************/
void* f()
{
    int n = 0;

    for(n = 0; n < 1000; ++n) 
    {
        atomic_fetch_add(&counter, 1); 
        ++cnt; 
    }
   
}
 /*****************************************************************************/
int main(void)
{
    int n = 0;

    pthread_t thr[10];

    for(n = 0; n < 10; ++n)
        pthread_create(&thr[n], NULL, &f, NULL);
    for(n = 0; n < 10; ++n)
        pthread_join(thr[n], NULL);
 
    printf("The atomic counter is %u\n", counter);
    printf("The non-atomic counter is %u\n", cnt);

    return 0;
}
