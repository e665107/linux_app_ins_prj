#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <pthread.h>
#include <sys/mman.h>

#include "misc_f.h"

#define BUFES PIPE_BUF
#define MAX 1024

typedef struct arg_struct ARG;

struct arg_struct{
    char arg1[10];
    int arg2;
    float arg3;
};

static int system_f(void);
static int time_f(void);
static int sleep_f(void);
static int sigaction_f(void);
static int sigmask_f(void);
static int sigpending_f(void);
static int timer_f(void);
static int pipe_f (void) ;
static int mkfifo_f(void);
static int sem_f( void );
static int shm_f (void);
static int pthread_cancel_f (void);
static int pthread_cleanup_f (void);
static int pthread_arg_f(void);
static int file_status_f(void);
static int fsync_f(void);
static int lseek_f(void);
static int mmap_f(void);

void f1(int **p)
{
    *p = (int *)malloc(sizeof(int));
}

void f2(int *p)
{
    printf("the heap is %d\n", *p);
}

int malloc_f(void)
{
    int *p;
            
    f1(&p);
    *p = 4;
    f2(p);

    free(p); 
    f2(p); 
    
    return 0;
}

int putenv_f(void)
{
    char * p;
    
    p = getenv("HOME");
    if(p == NULL){
        perror("fail to putenv");
        exit(1);
    }
    printf("$HOME is %s\n", p);
    
    if(putenv("HOME=/home/admin") == -1){
        perror("fail to putenv");
        exit(1);
    }
    
    p = getenv("HOME");
    if(p == NULL){
        perror("fail to putenv");
        exit(1);
    }
    printf("$HOME is %s \n", p); 

    if(putenv("ADMIN=hello") == -1){ 
        perror("fail to putenv");
        exit(1);
    }

    p = getenv("ADMIN");
    if(p == NULL){
        perror("fail to putenv");
        exit(1);
    }
    printf("$ADMIN is %s \n", p); 

    return 0;
}

/* rindex
   
   func: locate character in string
   
*/
char* basename(char*  full_name)
{
    char *p;
        
    p = rindex(full_name,'/');
        
    if (p == NULL)      
        p = full_name; 
    else 
        p++; 
        
    return p; 
}

int rindex_f()
{
    char *p;
    
    p = basename("/home/e66/linux_c_prj/my_test_ins/app/hello_world/misc_f.c");
    printf("file name is : %s\n", p); 
    
    return 0;
}

/*
  system: execute a shell command
*/
static int system_f(void)
{
    int fd;
    char buf[1024];
    int n;
    
    if(system("ls > build/temp.txt") == -1){
        perror("fail to exec command");
        exit(1);
    }
    
    if(fd = open("temp.txt", O_RDWR) == -1){
        perror("fail to open");
        exit(1);
    }
    
    if((n = read(fd, buf, 1024)) == -1){
        perror("fail to read");
        exit(1);
    }
    buf[n] = '\0';
    
    printf("%s", buf);
    
    return 0;
}

/*
  time: get time in seconds
*/
static int time_f( void )
{
    time_t cur_time;
    
    if ((cur_time = time (NULL)) == -1 ){
        perror ("time");
        exit (1);
    }
    
    printf ("the current time is : %ld \n", cur_time);
    
    exit(0);
}

void sigalrm_handler(int signo)
{
    printf("alarm sigprocess\n");
}

void sigusr1_handler(int signo)
{
    printf("catch SIGUSR1\n");
    
}

/*
  pause: wait for signal
*/
unsigned int my_sleep(unsigned int nsec)
{
    void (*p)(int );

    if( (p = signal(SIGALRM, sigalrm_handler)) == SIG_ERR){ 
        perror("can’t set handler for SIGALRM");
        exit(1);
    }

    alarm(nsec);

    pause();
    
    if(signal(SIGALRM, p) == SIG_ERR){
        perror("can’t rescue handler for SIGALRM");
        exit(1);
    }
    
    return alarm(0);
}

static int sleep_f(void)
{
    struct timeval begintime, endtime;
    float elapsed;
    unsigned int rest;
            
    if(signal(SIGUSR1, sigusr1_handler) == SIG_ERR){ 
        perror("can’t set handler for SIGUSR1");
        exit(1);
    }
    
    printf("the first time\n");
    printf("before sleeping\n");

    gettimeofday(&begintime, NULL);

    my_sleep(10);

    printf("after sleep\n");
    
    gettimeofday(&endtime, NULL);
    
    elapsed = 1000000 * (endtime.tv_sec - begintime.tv_sec) + 
              endtime.tv_usec - begintime.tv_usec; 
    elapsed /= 1000000;
    
    printf("elapsed time is %f\n", elapsed);
    
    printf("the second time\n");
    printf("before sleeping\n");

    gettimeofday(&begintime, NULL);
    
    rest = my_sleep(20);
    
    printf("after sleeping\n");
    gettimeofday(&endtime, NULL);

    elapsed = 1000000 * (endtime.tv_sec - begintime.tv_sec) + 
              endtime.tv_usec - begintime.tv_usec; 
    elapsed /= 1000000;
    
    printf("actual sleeping-time is %f\n", elapsed);
    printf("the rest is %u\n", rest);
    
    return 0;
}

/*
  sigaction
*/
static int sigaction_f(void)
{
    struct sigaction act;
        
    act.sa_handler = sigusr1_handler; 
    act.sa_flags = SA_NODEFER;
    act.sa_sigaction = NULL;
    
    sigemptyset(&act.sa_mask);

    if(sigaction(SIGUSR1, &act, NULL) == -1){
        perror("fail to set handler for SIGCHILD");
        exit(1);
    }

    printf("process begin\n");

    sleep(5);

    printf("done\n");
    
    return 0;
}

/*
  sigprocmask:

*/
static int sigmask_f(void)
{
    sigset_t set;
    
    if(signal(SIGUSR1, sigusr1_handler) == SIG_ERR){
        perror("can’t set handler for SIGUSR1");
        exit(1);
    }

    sigemptyset(&set);  /* 信号集初始化为0 */
    sigaddset(&set, SIGUSR1 - 1);

    if(sigprocmask(SIG_BLOCK, &set, NULL) == -1){  /*  */
        perror("fail to set signal-mask");
        exit(1);
    }
    
    printf("SIGUSR1 is not available\n");

    sleep(10);

    if(sigprocmask(SIG_UNBLOCK, &set, NULL) == -1){ 
        perror("fail to set signal-mask");
        exit(1);
    }

    printf("SIGUSR1 is available now\n");

    sleep(10);

    return 0;
}

static int sigpending_f(void)
{
    sigset_t set;
    sigset_t sig_pend;

    sigemptyset(&set);
    sigemptyset(&sig_pend);
    
    if(signal(SIGUSR1, sigusr1_handler) == SIG_ERR){
        perror("can’t set handler for SIGUSR1");
        exit(1);
    }
    
    sigaddset(&set, SIGUSR1 - 1); 
    
    if(sigprocmask(SIG_BLOCK, &set, NULL) == -1){ 
        perror("fail to set signal-mask");
        exit(1);
    }
    
    sleep(10); 

    if(sigpending(&sig_pend) == -1){  
        perror("fail to get pending signal");
        exit(1);
    }
    
    if(sigismember(&sig_pend, SIGUSR1 - 1) == 1) 
        printf("there is a signal, SIGUSR1, is pending\n");
    else{
        perror("fail to test signal-set");
        exit(1);
    }
    
    if(sigprocmask(SIG_UNBLOCK, &set, NULL) == -1){ 
        perror("fail to set signal-mask");
        exit(1);
    }
    
    printf("SIGUSR1 is available again\n");

    return 0;
}

void timer_handler(int signo)
{
    if(signo == SIGALRM){
        printf("the time is now\n");

        /* exit(0); */
    }else
        printf("unexpected signal\n");
}

static int timer_f(void)
{
    if(signal(SIGALRM, timer_handler) == SIG_ERR){
        perror("can’t set handler for SIGALRM");
        exit(0);
    }

    alarm(1);

    while(1)
    {
        printf("too early\n");
        sleep(2);
    }
        
    printf("should not be here, never\n");
    
    return 0;
}

void err_quit(char * msg)
{
    perror( msg );
    exit(1);
}

/*
  pipe:fd0----read  fd1---write

*/
static int pipe_f ( void ) 
{
    int fd[2];
    char buf[BUFES]; 
    pid_t pid;
    int len;
    
    if ( (pipe(fd)) < 0 ) 
        err_quit( "pipe" );
    
    if ( (pid = fork()) < 0 )  
        err_quit("fork");
    else if ( pid == 0 ){   
        close ( fd[0] );
        write(fd[1], "welcome china\n", 14 );  
        exit(0);
    }
    
    if ( (pid = fork()) < 0 )  
        err_quit("fork");
    else if ( pid > 0 ){   
        close ( fd[0] );
        close ( fd[1] );
        exit ( 0 );
    }
    else {      
        close ( fd[1] );  
        len = read (fd[0], buf, BUFES); 
        write(STDOUT_FILENO, buf, len);
        exit(0);
    }
}

static int mkfifo_f(void)
{
    mode_t mode = 0666; 
    char* fifo_name = "./build/hello";
    if ( ( mkfifo (fifo_name, mode )) < 0) {  
        perror ( "failed to mkfifo" );
        exit ( 1 );
    }
    else
        printf ("you successfully create a FIFO name is : %s\n", fifo_name);

    exit (0);
}

/*
 */
static int sem_f( void )
{
    int sem_id;
    int nsems = 1;
    int flags = 0666;
    struct sembuf buf;
    
    sem_id = semget(IPC_PRIVATE, nsems, flags);  /* create a new semaphore */
    
    if ( sem_id < 0 ){
        perror( "semget ") ;
        exit (1 );
    }

    printf ( "successfully created a semaphore : %d\n", sem_id );   
    buf.sem_num = 0;        
    buf.sem_op = 1;     
    buf.sem_flg = IPC_NOWAIT;   
    
    if ( (semop( sem_id, &buf, nsems) ) < 0) { 
        perror ( "semop");
        exit (1 ); 
    }
    
    system ( "ipcs -s " );   
    exit ( 0 );
}

static int shm_f (void)
{
    int shm_id ;
    char * shm_buf;
    
    shm_id = atoi("3");    
    
    if ( (shm_buf = shmat(shm_id, 0, 0)) < (char *) 0 ){
        perror ( "shmat" );
        exit (1);
    }
    
    printf ( " segment attached at %p\n", shm_buf );  
    system("ipcs -m");
    
    sleep(3); 

    if ( (shmdt(shm_buf)) < 0 ) {   
        perror ( "shmdt");
        exit(1);
    }
    
    printf ( "segment detached \n" );
    system ( "ipcs -m " );     
    
    exit ( 0 );
}

void * tfn1(void * arg)
{
    printf("new thread\n"); 
    sleep(10); 
}

/*
  pthread_cleanup_push:
  pthread_cleanup_pop:
*/
void *tfn2(void *arg)
{
    int a = 1;
    
    printf("the second thread \n");
    pthread_cleanup_push(cleanup, &a); 

    a = 2;

    pthread_cleanup_push(cleanup, &a); 

    /* pthread_exit(NULL);  */
    pthread_cleanup_pop(0); 
    pthread_cleanup_pop (0);

    return NULL;
}

void cleanup(void *arg)
{
    printf("No. %d clean-up procdure\n", *((int *)arg)); 
}

static int pthread_cancel_f (void)
{
    pthread_t tid;
    void * res;
    int err;
    
    err = pthread_create(&tid, NULL, tfn1, NULL); 
    if(err != 0){
        printf("can’t create thread %s\n", strerror(err));
        exit(1);    
    }
    
    err = pthread_cancel(tid); 
    if(err != 0){
        printf("can’t cancel thread %s\n", strerror(err));
        exit(1);    
    }
    
    err = pthread_join(tid, &res); 
    if(err != 0){
        printf("can’t join thread %s\n", strerror(err));
        exit(1);    
    }
    
    if(res == PTHREAD_CANCELED)
        printf("thread %u has been canceled\n", (unsigned int)tid);
    else
        printf("error\n"); 
    exit(0);
}

static int pthread_cleanup_f (void)
{
    pthread_t tid1, tid2, tid3, tid4;
    int err;
    
    err = pthread_create(&tid2, NULL, tfn2, NULL); 
    if(err != 0){
        printf("can’t create thread %s\n", strerror(err));
        exit(1);    
    }
    
    err = pthread_join(tid2, NULL); 
    if(err != 0){
        printf("can’t join thread %s\n", strerror(err));
        exit(1);    
    }

    return 0;
}


void * thfn(void * arg)
{
    pthread_t tid;
    pid_t pid;

    ARG * p = (ARG *)arg;
    tid = pthread_self();
    pid = getpid();

    printf("arg1 is : %s, arg2 is : %d, arg3 is : %f\n", p->arg1, p->arg2, p->arg3); 
    printf("the new thread: pid is: %u, tid is: %u\n", (unsigned int)pid, (unsigned int)tid);

    pthread_exit((void *) 3);       
    /* return NULL; */
}

/*
  pass the arg
*/
static int pthread_arg_f()
{
    pthread_t tid;
    ARG arg;                                            
    int err;
    void * res; 
    
    strcpy(arg.arg1, "123");
    arg.arg2 = atoi("456");
    arg.arg3 = atof("8910");
    
    err = pthread_create(&tid, NULL, thfn, (void *)&arg);               
    if(err != 0){
        printf("can’t create thread %s\n", strerror(err));
        exit(1);    
    }

    err = pthread_join(tid, &res);
    if(err != 0){
        printf("can’t join thread %s\n", strerror(err));
        exit(1);    
    }

    printf("result from thd: %d\n", (int)(res));


    return 0;
}

static int file_status_f(void)
{
    int fd;
    int flag;
    char *p = "1st linux"; /* 测试使用的字符串 */
    char *q = "2nd linux";
#if 0
    fd = open("./build/test0.txt", O_RDWR | O_CREAT); /* 该文件只写打开 */

    flag = fcntl(fd, F_GETFL, 0); /* 先使用F_GETFL命令得到文件状态标志 */
    if(flag == -1) {
        perror("fail to fcntl");
        exit(1);
    }
    flag |= O_APPEND | O_RDWR; /* 将文件状态标志添加"追加写"选项 */
    
    if(fcntl(fd, F_SETFL, flag) == -1){ /* 将文件状态修改为追加写 */
        perror("fail to fcntl");
        exit(1);
    }
#endif
    system("chmod +777 ./build/test.txt");

    fd = open("./build/test.txt", O_CREAT|O_RDWR); /* 该文件只写打开 */
    if(fd == -1)
    {
        perror("fail to open");
        exit(1);
    }
    
    if(write(fd, p, strlen(p)) == -1)
    { /* 输入新内容，该内容会覆盖部分旧的内容 */
        perror("fail to write");
        exit(1);
    }
    
    flag = fcntl(fd, F_GETFL, 0); /* 先使用F_GETFL命令得到文件状态标志 */
    if(flag == -1) {
        perror("fail to fcntl");
        exit(1);
    }
    flag |= O_APPEND; /* 将文件状态标志添加"追加写"选项 */
    
    if(fcntl(fd, F_SETFL, flag) == -1){ /* 将文件状态修改为追加写 */
        perror("fail to fcntl");
        exit(1);
    }

    if(write(fd, q, strlen(q)) == -1){ /* 再次输入新内容，该内容会追加在旧内容的后面 */
        perror("fail to write");
        exit(1);
    }
    close(fd); /* 关闭文件 */
    return 0;
}

/* fsync */
static int fsync_f(void)
{
    int fd;
    int i;

    fd = open("./build/test.txt", O_RDWR); /* 打开一个文件，其打开方式为可写 */
    if(fd == -1){
        perror("fail to open");
        exit(1);
    }
    
    i = 0;
    while(i < 3){
        sleep(5); /* 休眠五秒钟 */

        printf("hello\n");
        if(write(fd, "hello\n", 6) == -1){ /* 向文件输出一行字符串作为提示信息 */
            perror("fail to write");
            exit(1);
        }
        
        if(fsync(fd) == -1){ /* 输出信息后立即进行文件同步，保证输出信息即时写回到磁盘上 */
            perror("fail to fsync");
            exit(1);
        }

        i++;
    }

    close(fd); /* 关闭文件 */
    exit(0);
    
    return 0;
}

static int lseek_f(void)
{
    int fd;
    off_t off;
    char buf[MAX];

    fd = open("./build/test.txt", O_RDWR); /* 打开一个文件 */
    if(fd == -1){
        perror("fail to open");
        exit(1);
    }

    printf("before reading\n"); /* 输出提示信息 */

    off = lseek(fd, 0, SEEK_CUR); /* 调用lseek函数得到当前文件的读写位置 */
    if(off == -1){
        perror("fail to lseek");
        exit(1);
    }
    
    printf("the offset is : %d\n", off); /* 输出提示信息 */

    if(read(fd, buf, 5) == -1){ /* 读取5个字节的文件内容 */
        perror("fail ot read");
        exit(1);
    }

    printf("after reading\n"); /* 输出提示信息 */
    
    off = lseek(fd, 0, SEEK_CUR); /* 再次调用lseek函数得到当前文件的读写位置 */
    if(off == -1){
        perror("fail to lseek");
        exit(1);
    }
    
    printf("the offset is : %d\n", off); /* 输出结果 */

    close(fd); /* 关闭文件 */
    exit(0);
    return 0;
}

static int mmap_f(void)
{
    int fd;
    char *buf;
    int i;
    struct stat statbuf;
    
    if(stat("./build/test.txt", &statbuf) == -1){ /* 得到一个文件的状态信息，得到文件的大小 */
        perror("fail to get stat");
        exit(1);
    }

    fd = open("./build/test.txt", O_RDONLY); /* 以只读方式打开文件 */
    if(fd == -1){
        perror("fail to open");
        exit(1);
    }

    /* 建立一个内存映射，起始地址由系统为用户选择，并作为返回值返回
    * 建立的映射区的大小为打开的文件的大小
    * 访问权限为只读，属性为不会写到磁盘，防止对其进行写的误操作
    */
    buf = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(buf == MAP_FAILED){
        perror("fail to mmap");
        exit(1);
    }

    i = 0;
    while(i < statbuf.st_size){ /* 输出每一个字符，注意mmap函数不会添加’\0’结束符 */
        printf("%c", buf[i]);
        i++;
    }
    printf("\n");
    
    if(munmap(buf, statbuf.st_size) == -1){ /* 撤销内存映射 */
        perror("fail to munmap");
        exit(1);
    }

    close(fd); /* 关闭文件 */
    
    return 0;
}

void misc_fun_test()
{
    malloc_f();
    /* putenv_f(); */
    /* rindex_f(); */
    /* system_f(); */
    /* time_f(); */
    /* sleep_f(); */
    /* sigaction_f(); */
    /* sigmask_f(); */
    /* timer_f(); */
    /* pipe_f(); */
    /* mkfifo_f(); */
    /* sem_f(); */
    /* shm_f(); */
    /* pthread_cancel_f(); */
    /* pthread_cleanup_f(); */
    /* pthread_arg_f(); */
    /* file_status_f(); */
    /* fsync_f(); */
    /* lseek_f(); */
    /* mmap_f(); */
    exit(EXIT_SUCCESS);

}










