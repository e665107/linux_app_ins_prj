#ifndef FUNC_TESTS_H
#define FUNC_TESTS_H

    
/* #define SORT_FUNC */
/* #define DBLIST_FUNC */
/* #define STACK_ARRAY_FUNC */
/* #define STACK_LIST_FUNC */
#define BIG_LITTLE_ENDIAN_FUNC

/* #define WAIT3_FUNC */
/* #define MSG_FUNC */
/* #define FILE_BUFFERIO_FUNC */
/* #define CLIENT_SERVER_FUNC */
/* #define MISC_CC_FUNC */

#ifdef SORT_FUNC
#include "sort_f.h"
#endif // MACRO

#ifdef DBLIST_FUNC
#include "double_list_f.h"
#endif // MACRO

#ifdef STACK_ARRAY_FUNC
#include "stack_array_f.h"
#endif

#ifdef STACK_LIST_FUNC
#include "stack_list_f.h"
#endif

#ifdef BIG_LITTLE_ENDIAN_FUNC
#include "big_little_endian_f.h"
#endif // MACRO

#ifdef COPY_FUNC
#include "copy_f.h"
#endif // COPY_FUNC

#ifdef CLIENT_SERVER_FUNC
#include "socket_c_s.h"
#endif // MACRO

#ifdef MSG_FUNC
#include "msg_queue_f.h"
#endif // MACRO


#endif /* FUNC_TESTS_H */





