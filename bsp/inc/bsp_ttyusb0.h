#ifndef BSP_TTYUSB0_H
#define BSP_TTYUSB0_H


extern int serial_fd;

int bsp_ttyusb0_init(void);

int uart_recv(int fd, char *data, int datalen);

int uart_send(int fd, char *data, int datalen);


#endif /* BSP_TTYS0_H */
