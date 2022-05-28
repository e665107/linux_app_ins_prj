#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> //文件控制定义  
#include <termios.h>//终端控制定义
#include <errno.h>
#include "debug.h"
#include "bsp_ttyusb0.h"

int serial_fd = 0;

/* #define DEVICE  "/dev/ttyUSB0" */

int bsp_ttyusb0_init(void)
{
    struct termios options;
    
    /* serial_fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY); */
    serial_fd = open("/dev/ttymxc2", O_RDWR | O_NOCTTY);

    if (serial_fd < 0)
    {
        perror("open");
        return -1;
    }

    EDEBUG_LOCATION;
    tcgetattr(serial_fd, &options);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag &= ~CRTSCTS;
    options.c_cflag |= CS8;
    options.c_cflag &= ~CSTOPB;
    options.c_iflag |= IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    cfsetospeed(&options, B115200);
    tcflush(serial_fd, TCIFLUSH);
    tcsetattr(serial_fd, TCSANOW, &options);
    return 0;
}

/**
 *串口发送数据
 *@fd:串口描述符
 *@data:待发送数据
 *@datalen:数据长度
 */
int uart_send(int fd, char *data, int datalen)
{
    int len = 0;
    len = write(fd, data, datalen);//实际写入的长度

    if (len == datalen)
        return len;

    else
    {
        tcflush(fd, TCOFLUSH);//TCOFLUSH刷新写入的数据但不传送
        return -1;
    }

    return 0;
}

/**
 *串口接收数据
 *要求启动后，在pc端发送ascii文件
 */
int uart_recv(int fd, char *data, int datalen)
{
    int len = 0, ret = 0;
    fd_set fs_read;
    struct timeval tv_timeout;
    FD_ZERO(&fs_read);
    FD_SET(fd, &fs_read);
    tv_timeout.tv_sec  = (10 * 20 / 115200 + 2);
    tv_timeout.tv_usec = 0;
    ret = select(fd + 1, &fs_read, NULL, NULL, &tv_timeout);

    /* printf("ret = %d\n", ret);   */
//如果返回0，代表在描述符状态改变前已超过timeout时间,错误返回-1

    if (FD_ISSET(fd, &fs_read))
    {
        len = read(fd, data, datalen);
        /* printf("len = %d\n", len);   */
        return len;
    }

    else
    {
        perror("select");
        return -1;
    }

    return 0;
}


