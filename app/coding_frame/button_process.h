#ifndef _BUTTON_PROCESS_H
#define _BUTTON_PROCESS_H
/* os */
#include "coding_frame_creat.h"

void button_task_create(uint8_t priority_1);
uint32_t is_button_detected(void);


/* extern SemaphoreHandle_t button_b_sem; */

#endif /* _BUTTON_PROCESS_H */


 
