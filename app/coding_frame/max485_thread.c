
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include "thread_common.h"
#include "max485_thread.h"
#include "bsp_max485.h"
#include "delay.h"
#include "bsp_led.h"
#include "bsp_buzz.h"

void* thread_0(void *arg)
{
    char buf[]="hello world\r\n";
    static int times_cnt = 0;
    printf("Thread0 is created\n");

    for(;;)
    {
        bsp_max485_send(max485_fd_ins,  buf, strlen(buf));
        times_cnt++;
        /* if(times_cnt > 10) */
        /*     break; */
        
        sleep(2);
        led_toggle(led_fd);
        
        /* buzz_toggle(buzz_fd); */
        printf("times_cnt is %d\n", times_cnt);
    }

    /* exit(EXIT_SUCCESS); */
}

void* thread_1(void *arg)
{
    pthread_t newthid;
    char buf1[5] = {0};
    static int times_cnt = 0;
    int nread = 0;
    newthid = pthread_self();
    printf("Thread1 is created\n");

    for(;;)
    {
        nread = bsp_max485_recv(max485_fd_ins,   buf1, sizeof(buf1));
        printf("%s\n", buf1);
        printf("nread is %d\n", nread);
        if(nread > 0)
        {
            times_cnt++;
            nread = 0;
        }
        if(times_cnt > 10)
            /* times_cnt = 0;  */
            break;
        sleep(3);

        printf("times_cnt is %d\n", times_cnt);
    }
    exit(EXIT_SUCCESS);
}

#if 0
int create_max485_threads(void)
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

    pthread_join(th_id, NULL);
    exit(EXIT_SUCCESS);
}
#endif

int create_max485_threads(int priority)
{

    thread_struct thread0_str, thread_str;
    /* delay_ms(10); */
    start_thread(&thread0_str,  NULL,  thread_0);
    set_thread_priority(&thread0_str, priority);
    start_thread(&thread_str,  NULL,  thread_1);
    set_thread_priority(&thread_str, priority+1);
    
    pthread_join(thread_str.thread_id, NULL);
    exit(EXIT_SUCCESS);
}





