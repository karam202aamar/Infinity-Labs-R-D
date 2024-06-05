#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define MAX 50
  
/* structure for message queue */
struct mesg_buffer 
{
    long mesg_type;
    char mesg_text[100];
} message;
  
int main()
{
    key_t key;
    int msgid, i;
    char *str[MAX] = {"karam", "abrahem", "Aamar"};

    /* ftok to generate unique key */
    key = ftok("progfile.txt", 65);

    /* check if ftok failed*/
    if (-1 == key) 
    {
        perror("ftok error");
        return 1;
    }
    /* msgget creates a message queue */
    msgid = msgget(key, 0666 | IPC_CREAT);

    /*check if msgget failed*/
    if (-1 == msgid) 
    {
        perror("msgget error");
        return 1;
    }

    /*get strings from the user*/
    /* printf("Write Data: ");
    for(i = 0; i < 3; ++i)
    {
        fgets(str[i], MAX, stdin);
    } */
    message.mesg_type = 1;

    /*write the input to message queue*/
    for(i = 0; i < 3; ++i)
    {
        strcpy(message.mesg_text, str[i]);
        /* maybe must add one */
        if (msgsnd(msgid, &message, strlen(message.mesg_text) + 1, 0) == -1) 
        {
            perror("msgsnd error");
        }
    }
    
    return 0;
}

