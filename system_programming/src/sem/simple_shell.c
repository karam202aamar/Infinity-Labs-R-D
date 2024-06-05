/*******************************************************************************
 * Project: simple shell
 * Date: 09/11/2022
 * Name: karam aamar
 * Reviewer: aner
 * Version: 1.0
*******************************************************************************/
#include "simple_shell.h"
/******************************************************************************/
#include <string.h>	/*strcmp*/
#include <stdio.h>	/*pritf*/
#include <unistd.h> /*execvp*/
#include <stdlib.h> /*system*/
#include <sys/wait.h> /*wait*/

/******************************************************************************/
static int SystemProgIMP();
static int ForkProgIMP();
/******************************************************************************/
enum {CHILD_PROCESS = 0, NOT_EXIT_COMMAND = 1, COMMAND_LINE_LENTGH = 100};
/******************************************************************************/
int SimpleShell(const char *chosen_prog)
{
    int status = 0;

    /*check the input of the user*/
    if(!strcmp(chosen_prog, "fork"))
	{
        /*call fork function*/
		status = ForkProgIMP();
	}
	else if(!strcmp(chosen_prog, "system"))/*put in foo*/
	{
        /*call system function*/
		status = SystemProgIMP();
	}
	else
	{
		printf("the command not valid\n");
        
	}
    
	return status;
}
/******************************************************************************/
static int SystemProgIMP()
{
    /*define status*/
    int status = 0;
    /*define input buffer*/ 
    char input[COMMAND_LINE_LENTGH];

    char *ptr_to_end = NULL;
    char* fgets_retrun_val = NULL;

    /*loop untill we get exit input*/
    while(NOT_EXIT_COMMAND)
    {
        puts("enter your command: ");
        /*fgets to get a command from the user*/
        fgets_retrun_val = fgets(input, COMMAND_LINE_LENTGH, stdin);

        if(NULL == fgets_retrun_val)
        {
            return -1;
        }

        /*change the last chr to NULL terminator insted of '\n'*/
        ptr_to_end = strchr(input, '\n');
        *ptr_to_end = '\0';

        /*check if the input is exit*/
        if(!strcmp(input,"exit"))/*TODO:put as loop codition*/
        {
            /*end the loop*/
            return 0;
        }
        /*use system function - returns zero if no erros*/
        status = system(input);
    }
    return status;
}
/******************************************************************************/
static int ForkProgIMP()
{   
	/*define input buffer*/
	char input[COMMAND_LINE_LENTGH];
	
	/*define status variable*/
	int status = 0;

	/*define pid - process id*/
	int pid = 0;

	/*define **args the first element will be command the user insert , second is NULL*/
	char *args[] = {NULL, NULL, NULL ,NULL};
    
	char *ptr_to_end = NULL;
	char* fgets_retrun_val = NULL;
    
	const char deli[2] = " ";
	char *token = NULL;
	int runner = 0;
    
	int child_w_stat = 0;

	/*loop untill we get exit input*/
	while(1)
	{
		/*ask the user to enter a command*/
		puts("enter your command: ");

        	/*fgets to get a command from the user*/
        	fgets_retrun_val = fgets(input, COMMAND_LINE_LENTGH, stdin);

        	if(NULL == fgets_retrun_val)
        	{
            		return -1;
        	}

        	/*change the last chr to NULL terminator insted of '\n'*/
        	ptr_to_end = strchr(input, '\n');
        	*ptr_to_end = '\0';

        	token = strtok(input, deli);/*put in helper foo*/
        	while( token != NULL ) 
        	{
            		/*set the command we got in args*/
            		args[runner] = token;
            		token = strtok(NULL, deli);
            		++runner;
        	}

		/*Check if the given command is an exit command , if yes return zero*/
		if(!strcmp(input,"exit"))/*PUT AS LOOP CONDITION*/
		{
		    /*end the loop*/
		    return 0;
		}

        	/*call fork function & get the value when we call the fork*/
		pid = fork();

		/*if the return value from fork is zero then we are in the 
								child process */
        	if(CHILD_PROCESS == pid)
        	{
             		/*call execvp function - args(the user input(command for
             					 command line terminal), args)*/
			status = execvp(args[0], args);
            
            		if(-1 == status)
            		{
                		perror("execvp");
            		}
            		exit(status);
        	}
        	/*else if we are in the parent then wait */
        	else
        	{
            		wait(&child_w_stat);
            		WIFEXITED(child_w_stat);
        	}  
	}
	/*return the status*/
	return status;
}
/******************************************************************************/


























