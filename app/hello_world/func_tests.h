#ifndef FUNC_TESTS_H
#define FUNC_TESTS_H

    
/* #define COPY_FUNC */
/* #define GETLINE_FUNC */
/* #define MISC_FUNC */
/* #define MISC1_FUNC */
/* #define MISC2_FUNC */

/* #define WAIT3_FUNC */
/* #define MSG_FUNC */
/* #define FILE_BUFFERIO_FUNC */
#define CLIENT_SERVER_FUNC
/* #define MISC_CC_FUNC */
/* #define FIFO_CLIENT_SERVER_FUNC */


#ifdef MISC_FUNC
#include "misc_f.h"
#endif // MACRO

#ifdef FILE_BUFFERIO_FUNC
#include "file_io_buffer_f.h"
#endif // MACRO

#ifdef MISC1_FUNC
#include "misc_f1.h"
#endif

#ifdef MISC2_FUNC
#include "misc_f2.h"
#endif

#ifdef MISC_CC_FUNC
#include "misc_f.hpp"
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

#ifdef FIFO_CLIENT_SERVER_FUNC
#include "fifio_client_server.h"
#endif // FIFO_CLIENT_SERVER_FUNC

#endif /* FUNC_TESTS_H */





