#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
  
/* structure for message queue */
struct mesg_buffer 
{
    long mesg_type;
    char mesg_text[100];
} message;
  
int main()
{
    key_t key;
    int msgid;
    struct msqid_ds buf;

    /* ftok to generate unique key */
    key = ftok("progfile.txt", 65);
  
    /* msgget creates a message queue */
    /* and returns identifier */
    msgid = msgget(key, 0666 | IPC_CREAT);
    
    /* msgrcv to receive message */
    msgrcv(msgid, &message, sizeof(message), 0, IPC_NOWAIT);
    /* display the message */
    printf("Data Received is : %s \n",  message.mesg_text);
   
    msgctl(msgid, IPC_STAT, &buf);
    /*if the queue is empty*/
    if(0 == buf.msg_qnum)
    {
        /* delete the queue*/
        if (-1 == msgctl(msgid, IPC_RMID, NULL)) 
        {
            perror("msgctl error");
        }
        unlink("progfile.txt");
    }
  
    return 0;
}
