#ifndef THREAD_COMMON_H
#define THREAD_COMMON_H
#include <pthread.h>
#include <sched.h>


typedef struct 
{
    pthread_attr_t thread_attr;
    pthread_t thread_id;
    int policy;
    struct sched_param priority;
}thread_struct;

typedef void *(*thread_function_fp)(void *);


void start_thread(thread_struct *thread_param, void* app_param_struct, thread_function_fp thread_loop);

void set_thread_priority(thread_struct *thread_param, int priority);





#endif /* THREAD_COMMON_H */
