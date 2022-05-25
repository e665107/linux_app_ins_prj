#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "happy_hack1_thread.h"

void *thread_0(void *arg)
{
    char buf[]="hello world";

    printf("Thread0 is created\n");

    for(;;)
    {
        sleep(2);
        printf("Thread0 is running\n");
    }

    exit(EXIT_SUCCESS);
}

void *thread(void *arg)
{
    pthread_t newthid;
    char buf1[20];

    newthid = pthread_self();

    printf("The size of newthid is %ld\n", sizeof(newthid));
    printf("this is a new thread, thread ID = %ld\n", newthid);
    for(;;)
    {
        sleep(2);
        printf("Thread_happy_hack1 is running\n");

    }

    exit(EXIT_SUCCESS);
}

int create_happy_hack1_threads(void)
{
    pthread_t th_id;
    pthread_t th_id0;

    int status;

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

    pthread_join(th_id0, NULL);
    pthread_join(th_id, NULL);

    exit(EXIT_SUCCESS);
}
