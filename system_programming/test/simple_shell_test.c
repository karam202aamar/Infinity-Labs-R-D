/*******************************************************************************
 * Project: simple shell test
 * Date: 09/11/2022
 * Name: karam aamar
 * Reviewer: aner
 * Version: 1.0
*******************************************************************************/
#include <stdio.h>	/*puts*/
/******************************************************************************/
#include "simple_shell.h"
/******************************************************************************/
int main(int argc, char *argv[])
{
    int status = 0;
    
    /* if the user didn't enter which mode - fork by default */
    if(argc != 2)
    {
        status = SimpleShell("fork");
    }
    else
    {
        status = SimpleShell(argv[1]);
    }

    if(status)
    {
        puts("failed");
    }
    return 0;
}
/******************************************************************************/












