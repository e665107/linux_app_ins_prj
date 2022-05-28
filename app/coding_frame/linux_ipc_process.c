#include "linux_ipc_process.h" 
#include "bsp_led.h"

#ifdef IPC_PROCESS
void* thread_send(void *arg)
{
    char buf[]="hello world\r\n";
    static int times_cnt = 0;
    printf("ipc_thread0 is created\n");

    for(;;)
    {
        times_cnt++;
        sleep(2);
        led_toggle(led_fd);
        printf("times_cnt is %d\n", times_cnt);
    }

    /* exit(EXIT_SUCCESS); */
}

void* thread_receive(void *arg)
{
    pthread_t newthid;
    char buf1[5] = {0};
    static int times_cnt = 0;
    int nread = 0;
    newthid = pthread_self();
    printf("ipc_thread1 is created\n");
    for(;;)
    {
        
        sleep(3);
    }
    exit(EXIT_SUCCESS);
}


int create_ipc_threads(int priority)
{
    static thread_struct ipc_thread0_str, ipc_thread_str;
    /* delay_ms(10); */
    start_thread(&ipc_thread0_str,  NULL,  thread_send);
    set_thread_priority(&ipc_thread0_str, priority);
    start_thread(&ipc_thread_str,  NULL,  thread_receive);
    set_thread_priority(&ipc_thread_str, priority+1);
    
    pthread_join(ipc_thread_str.thread_id, NULL);
    exit(EXIT_SUCCESS);
}


#endif
