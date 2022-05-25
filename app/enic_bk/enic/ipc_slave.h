#ifndef _IPC_SLAVE_H
#define _IPC_SLAVE_H

typedef struct
{
        
} msgbuf_t;

int IPC_Init(void (*app_cb)(intptr_t));
uint32_t IPC_Msg_Send(intptr_t data);
#ifdef CONFIG_STATISTIC
void IPC_Report_Cumulative(void);
#endif

#endif /* _IPC_SLAVE_H */

