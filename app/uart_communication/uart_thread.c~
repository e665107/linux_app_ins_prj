#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "structures_thread.h"


#include "func_tests.h"

void *thread_0(void *arg)
{
    printf("Thread0 is created\n");

#ifdef DBLIST_FUNC
    dblist_test();
#endif // DBLIST_FUNC
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
    newthid = pthread_self();
    
    printf("The size of newthid is %d\n", sizeof(newthid));
    printf("this is a new thread, thread ID = %d\n", newthid);

    for(;;)
    {
        sleep(2);
        printf("Thread is running\n");
   
    }
    
    exit(EXIT_SUCCESS);
}

int create_structure_threads(void)
{
    pthread_t th_id;
    pthread_t th_id0;
    
    int status;
    
    printf("main thread ,ID is %d\n", pthread_self());
     
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
    exit(EXIT_SUCCESS);
}




