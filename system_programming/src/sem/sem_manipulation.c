/*******************************************************************************
 * Project: semaphore
 * Date: 20/11/2022
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
/******************************************************************/
enum{SUCCESS, FAILURE};
enum{SYSV_FAIL = -1, INIT_VAL = 0, SEM_POS = 0, NUM_OF_SEMS = 1, TOKEN = 3, INPUT = 20};
/******************************************************************/
#define SEMAPHORE_NAME        argv[1]
#define OPTION                tokens[0]
#define NUMBER                tokens[1]
/******************************************************************/
static int SemaphoreFuncIMP(char **argv);
static int TokensImp(char *input, char **tokens);
static int PrintValueIMP(int *my_sem);
static int IncrementSemIMP(int number, int sem_id, char *undo_cmd);
static int DecrementSemIMP(int number, int sem_id, char *undo_cmd);
static void SemDestroyIMP(int sem_id);
/******************************************************************/
union semun {
    int val;               /* used for SETVAL only */
    struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
    unsigned short *array;         /* used for GETALL and SETALL */
};
/******************************************************************/
int main(int argc, char **argv)
{
    /* check num of argc */
    if(1 >= argc)
    {
        puts("GIVE A NAME FOR THE SEMAPHORE");
        return 0;
    }
    /*call semaphore function(argc, argv)*/
    if(SemaphoreFuncIMP(argv))
    {
        puts("SOMETHING WENT WRONG!");
    }
    else
    {
        puts("SUCCESS!");
    }
    return 0;
}
/******************************************************************/
static int SemaphoreFuncIMP(char **argv)
{    
    int number, status = SUCCESS;
    /*define key*/
    key_t key;
    /*define semaphore id*/
    int sem_id;
    /* define array for the input*/
    char input_string[INPUT] = {0};
    /* define array for token strings */
    char *tokens[TOKEN] = {NULL};
    /*define variable for num of tokens*/
    int tokens_num = 0;
    /*create semaphore value for semctl()*/
    union semun sem_val;
    
    /*init the first semaphore value */
    sem_val.val = 10;
    /*create a key identifier*/
    key = ftok(SEMAPHORE_NAME, 'E');

    /*handle failures - key*/
    if(SYSV_FAIL == key)
    {
        perror("failed ftok");
        return FAILURE;
    }

    /*create a semaphore*/
    sem_id = semget(key, NUM_OF_SEMS, 0666 | IPC_CREAT);
    
    /*handle failures - semget*/
    if(SYSV_FAIL == sem_id)
    {
        perror("failed semget");
        return FAILURE;
    }

    /*handle failures - init semaphores*/
    if(SYSV_FAIL == semctl(sem_id, SEM_POS, SETVAL, sem_val.val))
    {
        perror("failed semctl");
        return FAILURE;
    }

    /* loop */
    while (1)
    { 
        puts("enter your command:");
        /*call fgets*/
        if (!fgets(input_string, INPUT, stdin))
        {
            perror("fgets failed");
            return FAILURE;
        }
        /*call tokens function to init sperate the string & get num of tokens*/
        tokens_num = TokensImp(input_string, tokens);

        if (tokens_num > 3)
        {
            puts("invalid input");
        }
        else
        {
            /* check if it's a V || X */
            if (1 == tokens_num) 
            {
                /*if it's a V*/
                if (!strncmp("V", OPTION, 1))
                {
                    if (PrintValueIMP(&sem_id))
                    {
                        printf("V option failed, see previous prints\n");
                        status = FAILURE;
                        break;
                    }                  
                }
                /*if it's a X*/
                else if (!strncmp("X", OPTION, 1))
                {
                    puts("Exiting the program....");
                    /*delete semctrl*/
                    exit(0);   
                }
            }
            /*check if we got I || D */
            else 
            {
                /*check the inputof the number & "undo" command*/
                if (!(number = atoi(NUMBER)))
                {
                    puts("atoi failed");
                    return FAILURE;
                }
                
                /*if it's an I option*/
                if (!strcmp("I", OPTION))
                {
                    if (IncrementSemIMP(number, sem_id, tokens[2])) 
                    {
                        puts("I option failed");
                        status = FAILURE;
                        break;
                    }                   
                }
                /*if it's an D option*/
                else if (!strcmp("D", OPTION))
                {
                    if (DecrementSemIMP(number, sem_id, tokens[2])) 
                    {
                        printf("D option failed, see previous prints\n");
                        status = FAILURE;
                        break;
                    }  
                }         
            }
        }
    } 
    SemDestroyIMP(sem_id);

    return status;
}
/******************************************************************/
static int TokensImp(char *input, char **tokens)
{
    int counter = 0;
    /*get first word*/
    *tokens = strtok(input, " ");

    while (*tokens && TOKEN >= counter)
    {
        /*move to next word in the array of strig*/
        ++tokens;
        /*increment counter*/
        ++counter;
        /*call strtok again*/
        *tokens = strtok(NULL, " ");
    }
    return counter;
}         
/******************************************************************/
static int PrintValueIMP(int *my_sem)
{
    int ctl_ret = semctl(*my_sem, 0, GETVAL);

    if (-1 == ctl_ret)
    {
        perror("sem_getvalue failed");
        return FAILURE;
    }
    printf("semaphore current value is: %d\n", ctl_ret); 

    return SUCCESS; 
}
/******************************************************************/
static int IncrementSemIMP(int number, int sem_id, char *undo_cmd)
{
    int status = -1;
    /*define struct for the semaphore operations*/
    struct sembuf sem_op_inc;

    sem_op_inc.sem_num = 0;
    sem_op_inc.sem_op = number;

    if(NULL == undo_cmd)
    {
        sem_op_inc.sem_flg = IPC_NOWAIT ;
    }
    else if(!strncmp(undo_cmd, "[undo]",6))
    {
        
        sem_op_inc.sem_flg = SEM_UNDO;
    }
    else
    {
        return status;
    }

    status = semop(sem_id, &sem_op_inc, 1);
    
    return status;
}
/******************************************************************/
static int DecrementSemIMP(int number, int sem_id, char *undo_cmd)
{
    int status = -1;
    /*define struct for the semaphore operations*/
    struct sembuf sem_op_dec;

    sem_op_dec.sem_num = 0;
    sem_op_dec.sem_op = -number;
    printf("the values of char *undo_cmd : %s",undo_cmd);
    if(NULL == undo_cmd)
    {
        sem_op_dec.sem_flg = IPC_NOWAIT ;
    }
    else if(!strncmp(undo_cmd, "[undo]",6))
    {
        sem_op_dec.sem_flg = SEM_UNDO;
    }
    else
    {
        return status;
    }

    status = semop(sem_id, &sem_op_dec, 1);
    
    return status;
}
/******************************************************************/
static void SemDestroyIMP(int sem_id)
{
    if(semctl(sem_id, 0, IPC_RMID))
    {
        perror("failed to destroy semaphore");
    }
}
/******************************************************************/