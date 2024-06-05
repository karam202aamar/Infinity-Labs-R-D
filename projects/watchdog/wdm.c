/******************************************************************************/
#include <stdio.h>      
#include <stdlib.h>     
#include <assert.h>
#include <stdatomic.h>  

#include "watch_dog.h"
/******************************************************************************/
static volatile atomic_int g_tolerance_count = 0;
/******************************************************************************/
int main(int argc, const char *argv[])
{
    assert(argv[1]);
    assert(argv[2]);
    
    time_t interval = 0;
    size_t tolerance_count = 0;

    tolerance_count = (size_t)atoi(argv[1]);
    interval = (time_t)atoi(argv[2]);
    
    MakeMeImMortal(tolerance_count, interval, (char**)argv);

    return 0;
}
/******************************************************************************/
