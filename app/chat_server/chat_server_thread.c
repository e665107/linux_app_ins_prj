#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <signal.h>


#include "chat_server_thread.h"
#include "chat_server.h"


void *thread_0(void *arg)
{
    printf("Thread0 is created\n");

    chat_server_process();

    for(;;)
    {
        sleep(5);
        printf("Thread0 is running\n");
        
    }
    exit(EXIT_SUCCESS);
}

void *thread(void *arg)
{
    pthread_t newthid;
    newthid = pthread_self();
    
    printf("The size of newthid is %ld\n", sizeof(newthid));
    printf("this is a new thread, thread ID = %ld\n", newthid);

    for(;;)
    {
        sleep(2);
        printf("Thread1 is running\n");
    }
    exit(EXIT_SUCCESS);
}

int create_chat_server_thread()
{
    pthread_t th_id;
    pthread_t th_id0;
    pthread_attr_t thread0_attr;
    pthread_attr_t thread_attr;
    int status;
    int rs;
    
    printf("main thread ,ID is %ld\n", pthread_self());
     
    if (pthread_create(&th_id, NULL, (void *)thread, NULL) != 0)
    {
        printf("thread creation failed\n");
        exit(EXIT_FAILURE);
    }
    
    if (pthread_create(&th_id0, NULL, (void *)thread_0, NULL) != 0)
    {
        printf("thread_0 creation failed\n");
        exit(EXIT_FAILURE);
    }
    
    else
    {
        printf("thread_0 created successful\n");
    }
    
    pthread_join(th_id, NULL); /* 可以得到thread的返回值 */
    pthread_join(th_id0, NULL);
    exit(EXIT_SUCCESS);
}











