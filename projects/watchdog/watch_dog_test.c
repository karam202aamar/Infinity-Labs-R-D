/*******************************************************************************
 * Project: watchdog test file
 * Date: 01/12/22
 * Name: karam
 * Reviewer: 
 * Version: 1.0			
*******************************************************************************/
#include <stdio.h>  /* printf puts*/
#include <stdlib.h> /* malloc free */
/******************************************************************************/
#include "watch_dog.h"
/******************************************************************************/
static void ImplementFunc(char* argv[]);

/******************************************************************************/
int main(int argc, char* argv[])
{
	ImplementFunc(argv);
	
	return 0;
}
/******************************************************************************/
static void ImplementFunc(char* argv[])
{
    if(MakeMeImMortal(argv))
    {
        fputs("MakeMeImMortal function failed\n", stderr);
    }

    sleep(100);

    if(LetMeDie)
    {
        fputs("LetMeDie function failed\n", stderr);
    }
}
/******************************************************************************/
void catcher(int signum)
{
  puts("catcher() has gained control");
}

