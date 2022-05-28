#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define BUFSZ 4096

struct msg{   
    long msg_types;  
    char msg_buf[511]; 
};

int rcv_msg_f()
{
    int     qid;
    int         len;
    key_t key;
    struct msg pmsg;
    key = ftok("./app",'a');  //建立key值

    if ( (qid=msgget(key, IPC_CREAT | 0666)) < 0 ) {  
        perror ( "msgget" );
        exit (1) ;
    }

    
    len = msgrcv ( qid, &pmsg, BUFSZ, 0, MSG_NOERROR | IPC_NOWAIT);
    
    if ( len > 0 )
    {
        pmsg.msg_buf[len] = '\0';  
        printf ("reading queue id :%05d\n", qid ); 
        printf ("message type : %05ld\n", pmsg.msg_types ); 
        printf ("message length : %d bytes\n", len ); 
        printf ("mesage text: %s\n", pmsg.msg_buf);  
    }
    else if ( len == 0 )
        printf ("have no message from queue %d\n", qid );
    else {
        perror ( "msgrcv");
        exit (1);
    }
    /* system("ipcs -q")   ; */
    /* exit ( 0 ) ; */
}


int snd_msg_f( void )
{
    int     qid;
    int         pid;
    int         len;
    key_t key;
    struct msg pmsg;   
    void *ret;
    pmsg.msg_types = getpid();   
    sprintf (pmsg.msg_buf,"hello!this is :%d\n", getpid() );  
    len = strlen ( pmsg.msg_buf );  
    key = ftok("./app",'a');  //建立key值
    if ( (qid=msgget(key, IPC_CREAT | 0666)) < 0 ) {  
        perror ( "msgget" );
        exit (1) ;
    }
    
    if ( (msgsnd(qid, &pmsg, len, 0 )) < 0 ){  
        perror ( "msgsn" );
        exit ( 1 );
    }
    printf ("successfully send a message to the queue: %d \n", qid);
    /*
     * exit ( 0 ) ;
     */
    pthread_exit(ret);
}










