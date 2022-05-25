#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "enic_thread.h"
#include "test.h"

void *thread_enic(void *arg)
{
    char buf[]="hello world";

    printf("Thread_enic is created\n");

#ifdef SORT_FUNC
    sort_t();
#endif // MACRO
#ifdef STACK_ARRAY_FUNC
    stack_array_t();
#endif // stack_array_f.h
#ifdef STACK_LIST_FUNC
    stack_list_t();
#endif // STACK_LIST_FUNC
#ifdef BIG_LITTLE_ENDIAN_FUNC
    big_little_endian_t();
#endif // MACRO

    sampleTest();

    printf("sampleTest is over\n");

    printf("exit thread_enic\n");

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
        printf("%s\n", buf1);
        sleep(2);
        printf("Thread is running\n");
    }

    exit(EXIT_SUCCESS);
}

int create_enic_threads(void)
{
    pthread_t th_id;
    pthread_t th_id0;

    int status;

    printf("main thread ,ID is %ld\n", pthread_self());

    if (pthread_create(&th_id0, NULL, (void *)thread_enic, NULL) != 0)
    {
        printf("thread_0 creation failed\n");
        exit(EXIT_FAILURE);
    }

    else
    {
        printf("thread_0 created successful\n");
    }

    pthread_join(th_id0, NULL);
    exit(EXIT_SUCCESS);
}
