#include "thread_common.h"


void start_thread(thread_struct *thread_param, void* app_param_struct, thread_function_fp thread_loop)
{
    pthread_attr_init(&(thread_param->thread_attr));
    pthread_attr_setscope(&(thread_param->thread_attr), PTHREAD_SCOPE_SYSTEM);
    pthread_create(&(thread_param->thread_id), &(thread_param->thread_attr), thread_loop, app_param_struct);
}


void set_thread_priority(thread_struct *thread_param, int priority)
{
    pthread_getschedparam((*thread_param).thread_id, &(thread_param->policy), &(thread_param->priority));
    thread_param->policy = SCHED_RR;
    thread_param->priority.sched_priority = priority;
    pthread_setschedparam((*thread_param).thread_id, (*thread_param).policy, &(thread_param->priority));

}

