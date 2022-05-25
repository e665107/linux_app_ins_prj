#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "mysql_access_thread.h"
#include "bsp_ttyusb0.h"

void *thread_0(void *arg)
{
        
        for(;;)
        {
                sleep(2);
                printf("Thread0 is running\n");
        }

}

void *thread(void *arg)
{
        for(;;)
        {
                printf("Thread is running\n");
                sleep(2);
   
        }
        exit(EXIT_SUCCESS);
}

int create_mysql_access_threads(void)
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
        pthread_join(th_id, NULL);
        pthread_join(th_id0, NULL);
        exit(EXIT_SUCCESS);
}



