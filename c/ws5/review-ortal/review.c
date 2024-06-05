#include <stdio.h> /* printf, fgets, sizeof */
#include <string.h> /* strcmp, srncmp */
#include <stdlib.h> /* exit */

#define NUM_OF_HANDLERS 4

/* typedefs */

typedef int (* cmp_func)(char *, char *);
typedef void (* act_func)(char *, char *, FILE *);

typedef struct handler_ty
{
    char *cmd;
    cmp_func cmp;
    act_func act;
}handler_ty;

enum cmp_return {MATCH = 0, NO_MATCH = 1};

/* function declerations */

static void InitChain(handler_ty[]);
static void AppendFunc(char *, char *, FILE *);
static int ShouldExitRun(char *user_input, char *cmd);
static void ExitFunc(char *dummy, char *dummy2, FILE *my_file);
static int ShouldRemoveRun(char *user_input, char *cmd);
static void RemoveFunc(char *user_input, char *file_name, FILE *my_file);
static int ShouldCountRun(char *user_input, char *cmd);
static void CountFunc(char *user_input, char *file_name, FILE *my_file);
static int ShouldHeadAppendRun(char *user_input, char *cmd);
static void HeadAppendFunc(char *user_input, char *file_name, FILE *my_file);

/* main */

int main(int argc, char **argv)
{
    char user_input[280];
    FILE * my_file;
    handler_ty hnd_arr[NUM_OF_HANDLERS];
    int i;

    InitChain(hnd_arr);
    i = 0;
    printf("Please type your entry / command "
            "(no longer than a tweet (280c):\n");
    
    while (1)
    {
        fgets(user_input, 280, stdin);
        while (i < NUM_OF_HANDLERS)
        {
            if (MATCH == (hnd_arr[i].cmp(user_input, hnd_arr[i].cmd)))
            {
                hnd_arr[i].act(user_input, argv[1], my_file);
                fflush(stdin);
                memset(user_input, 0, 280);
            }
            ++i;
        }
        i = 0;
        AppendFunc(user_input, argv[1], my_file);
    }        

    return 0;
}

static void InitChain(handler_ty *chain)
{
    chain[0].cmd = "-exit";
    chain[0].cmp = ShouldExitRun;
    chain[0].act = ExitFunc;
    chain[1].cmd = "-remove";
    chain[1].cmp = ShouldRemoveRun;
    chain[1].act = RemoveFunc;
    chain[2].cmd = "-count";
    chain[2].cmp = ShouldCountRun;
    chain[2].act = CountFunc;
    chain[3].cmd = "<";
    chain[3].cmp = ShouldHeadAppendRun;
    chain[3].act = HeadAppendFunc;
    
}

static void AppendFunc(char *user_input, char *file_name, FILE *my_file)
{
    my_file = fopen(file_name, "a");
    fprintf(my_file, "%s", user_input);
    fclose(my_file);
    return;
}

/* returns 0 if a handler should perform its action */

static int ShouldExitRun(char *user_input, char *cmd)
{
    if (strncmp((const char *)user_input, (const char *)cmd, 5))
    {
        return NO_MATCH;
    }
    return MATCH;
}

static void ExitFunc(char *user_input, char *file_name, FILE *my_file)
{
    printf("exit command initiated\n");
    exit(0);
}

static int ShouldRemoveRun(char *user_input, char *cmd)
{
    if (strncmp((const char *)user_input, (const char *)cmd, 7))
    {
        return NO_MATCH;
    }
    return MATCH;
}

static void RemoveFunc(char *user_input, char *file_name, FILE *my_file)
{
    if (remove(file_name) == 0)
    {
        printf("File %s deleted successfully\n", file_name);
        exit(0);
    }
    else
    {
        printf("Error: file not deleted.");
    }
}

static int ShouldCountRun(char *user_input, char *cmd)
{
    if (strncmp((const char *)user_input, (const char *)cmd, 6))
    {
        return NO_MATCH;
    }
    return MATCH;
}

static void CountFunc(char *user_input, char *file_name, FILE *my_file)
{
    char buffer[200];
    int line_count;

    my_file = fopen(file_name, "r");
    line_count = 0;
    while (fgets(buffer, sizeof(buffer), my_file) != NULL)
    {
        line_count++;
    }
    printf("%s has %i lines.\n", file_name, line_count);
}

static int ShouldHeadAppendRun(char *user_input, char *cmd)
{
    if (strncmp((const char *)user_input, (const char *)cmd, 1))
    {
        return NO_MATCH;
    }
    return MATCH;
}

/* You were in the middle of this one last night */

static void HeadAppendFunc(char *user_input, char *file_name, FILE *my_file)
{
    FILE * temp;
    char cpy;
    
    temp = fopen("temp.txt", "a");
    if (temp == NULL)
    {
        printf("Could not open temp file.");
        exit(0);
    }
    
    /* places string at head of temp */

    user_input = user_input + 1;
    fputs(user_input, temp);
    fclose(temp);

    /* appends contents of my_file to temp */

    my_file = fopen(file_name, "r");
    temp = fopen("temp.txt", "a");
    cpy = fgetc(my_file);
    while (cpy != EOF)
    {
        fputc(cpy, temp);
        cpy = fgetc(my_file);
    }
    fclose(temp);
    fclose(my_file);

    /* writes temp back onto my_file */

    my_file = fopen(file_name, "w");
    fseek(my_file, 0, SEEK_SET);
    temp = fopen("temp.txt", "r");
    fseek(temp, 0, SEEK_SET);
    cpy = fgetc(temp);
    while (cpy != EOF)
    {
        fputc(cpy, my_file);
        cpy = fgetc(temp);
    }
    fclose(temp);
    fclose(my_file);
    remove("temp.txt");
} 

