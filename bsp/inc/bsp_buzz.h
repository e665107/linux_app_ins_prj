#ifndef BSP_BUZZ_H
#define BSP_BUZZ_H
#include "bsp_hal.h"
extern int buzz_fd;

void bsp_buzz_off(int fd);

void bsp_buzz_on(int fd);

void bsp_buzz_init(void);

void buzz_toggle(int fd);



#endif /* BSP_BUZZ_H */
