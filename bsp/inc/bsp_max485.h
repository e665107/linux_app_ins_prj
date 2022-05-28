#ifndef BSP_MAX485_H
#define BSP_MAX485_H


int bsp_max485_recv(int max485_fd,  char* buffer, int size);


int bsp_max485_send(int max485_fd, const char* buffer, int size);


int bsp_max485_init(void);

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);

extern int max485_fd_ins;
extern int max485_ctrl_fd_ins;




#endif /* BSP_MAX485_H */ 
