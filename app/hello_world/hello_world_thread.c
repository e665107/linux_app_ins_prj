#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <signal.h>


#include "hello_world_thread.h"
#include "func_tests.h"


int global;

void *thread_0(void *arg)
{
    printf("Thread0 is created\n");

#ifdef COPY_FUNC
    copy_f_test();
#endif

#ifdef GETLINE_FUNC
    get_line_f_test();
#endif

#ifdef MISC_FUNC
    misc_fun_test();
#endif // MISC_FUNC
    
#ifdef MISC1_FUNC
    misc1_fun_test();
#endif // MISC_FUNC

#ifdef MISC2_FUNC
    misc2_fun_test();
#endif // MISC_FUNC

    
#ifdef FILE_BUFFERIO_FUNC
    file_io_func_t();
#endif // FILE_BUFFERIO_FUNC

#ifdef MISC_CC_FUNC
    misc_fun_cpp_test();
#endif // MISC_CC_FUNC
    
    for(;;)
    {
        sleep(5);
        printf("Thread0 is running\n");
        
#ifdef MSG_FUNC
        rcv_msg_f();
#endif // MSG_FUNC

#ifdef CLIENT_SERVER_FUNC
        client_f();
#endif

#ifdef FIFO_CLIENT_SERVER_FUNC
        fifo_client();
#endif // MACRO
        
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
        
#ifdef CLIENT_SERVER_FUNC
        server_f();
#endif // MACRO

#ifdef MSG_FUNC
        snd_msg_f();
#endif
        
#if 0       
        if(raise(SIGUSR1) == 0)
            break;
#endif
        
#ifdef FIFO_CLIENT_SERVER_FUNC
        fifo_server();
#else
        sleep(2);
#endif // MACRO

        printf("Thread is running\n");
   
    }

    exit(EXIT_SUCCESS);
}

int create_thread()
{
    pthread_t th_id;
    pthread_t th_id0;
    pthread_attr_t thread0_attr;
    pthread_attr_t thread_attr;
    int status;
    int rs;
    
    /* rs = pthread_attr_init(&thread0_attr); */
    /* assert(rs==0); */
    /* rs = pthread_attr_init(&thread_attr); */
    /* assert(rs==0); */
#ifdef WAIT3_FUNC
    create_process();
    while(1);
#endif // WAIT3_FUNC    


#ifdef CLIENT_SERVER_FUNC

    create_client_server_process();
    while(1);
#endif // CLIENT_SERVER_FUNC
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

/*
  fork:
  vfork: create a child process and block parent, 
*/
int create_process()
{
    pid_t pid;
    int stack = 1; 
    int *heap = NULL;
    struct rusage rusage;

    heap = (int *)malloc(sizeof(int)); 
    *heap = 2;
    
    pid = fork();
    
    if(pid < 0){
        printf("fail to fork\n");
        exit(1);    
    }else if(pid == 0){
        /* create_thread();    */
        global++;
        stack++;
        (*heap)++;
        printf("the child, data : %d, stack : %d, heap : %d\n", global, stack, *heap);
        exit(0);
    } else {
        /* create_thread(); */
    }
    if(wait3(NULL, 0, &rusage) == -1){
        perror("fail to wait");
        exit(1);
    }

    printf("utime is %d\n", rusage.ru_utime);
    printf("stime is %d\n", rusage.ru_stime);
    printf("maxrss is %ld\n", rusage.ru_maxrss); 
    printf("ixrss is %ld\n", rusage.ru_ixrss); 
    printf("idrss is %ld\n", rusage.ru_idrss);
    printf("isrss is %ld\n", rusage.ru_isrss);
    printf("minflt is %ld\n", rusage.ru_minflt);
    printf("majflt is %ld\n", rusage.ru_majflt);
    printf("nswap is %ld\n", rusage.ru_nswap);
    printf("inblock is %ld\n", rusage.ru_inblock);
    printf("oublock is %ld\n", rusage.ru_oublock);
    printf("msgsnd is %ld\n", rusage.ru_msgsnd);
    printf("msgrcv is %ld\n", rusage.ru_msgrcv);
    printf("nsignals is %ld\n", rusage.ru_nsignals);
    printf("nvcsw is %ld\n", rusage.ru_nvcsw);
    printf("nivcsw is %ld\n", rusage.ru_nivcsw);
    
    sleep(2);
    printf("the parent, data : %d, stack : %d, heap : %d\n", global, stack, *heap);
    exit(0);

    return 0;
}

int create_nozombie_process()
{
    pid_t pid;

    pid = fork();

    if(pid < 0){
        printf("fail to fork\n");
        exit(1);
    }else if(pid == 0){
        printf("the child\n");
        
        pid = fork();
        
        if(pid < 0){
            printf("fail to fork\n");
            exit(1);
        }else if(pid == 0){
            printf("do something you want\n");
            
            sleep(5);
            
            printf("done\n");
            exit(0);
        }else
            exit(0);
    }else
    {
        printf("the parent\n");
    }

    return 0;
}

/*
  
 */
int create_client_server_process()
{
    pthread_t th_id;
    pthread_t th_id0;

    pid_t pid;

    pid = fork();

    if(pid < 0){
        printf("fail to fork\n");
        exit(1);
    }else if(pid == 0){
        printf("the child\n");
        if (pthread_create(&th_id, NULL, (void *)thread, NULL) != 0)
        {
            printf("thread creation failed\n");
            exit(EXIT_FAILURE);
        }
    
        /* exit(0); */
    }else
    {
        printf("the parent\n");
        if (pthread_create(&th_id0, NULL, (void *)thread_0, NULL) != 0)
        {
            printf("thread_0 creation failed\n");
            exit(EXIT_FAILURE);
        }

    }

    return 0;    

}







