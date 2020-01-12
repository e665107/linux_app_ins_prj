/* header files */
#include "bsp_init.h"
#include "app_init.h"
/* #include "hello_world_thread.h" */


int main(int argc, char *argv[])
{
    /* system_init----------------------------------------------------------*/
    bsp_init();
    /* application_init----------------------------------------------------------*/
    app_init();
    /* Infinite loop */
    return 0;
}


#if 0
#include "my_client.h"
#endif
#if 0
#include "my_recv.h"
#endif
#if 0
#include "createthread.h"
#endif
#if 0
#include "app_thread_test.h"
#endif

#if 0
int main(int argc, char *argv[])
{
    /* my_client(argc, argv); */
    /* create_thread(); */

    /* init_serial(); */
    /* serial_process(argc, argv); */
    /* threaddata(); */
    /* copy( argc, argv); */

    return 0;
}
#endif






