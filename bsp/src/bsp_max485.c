#include "bsp_max485.h"
#include <unistd.h>
//#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>

int max485_fd_ins = 0;
int max485_ctrl_fd_ins = 0;

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;
    
    if(tcgetattr( fd, &oldtio)  !=  0) { 
        perror("SetupSerial 1");
        return -1;
    }
    bzero( &newtio, sizeof( newtio ) );
    newtio.c_cflag  |=  CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch( nBits )
    {
        case 7:
            newtio.c_cflag |= CS7;
            break;
        case 8:
            newtio.c_cflag |= CS8;
            break;
    }

    switch( nEvent )
    {
        case 'O':
            newtio.c_cflag |= PARENB;
            newtio.c_cflag |= PARODD;
            newtio.c_iflag |= (INPCK | ISTRIP);
            break;
        case 'E': 
            newtio.c_iflag |= (INPCK | ISTRIP);
            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
            break;
        case 'N':  
            newtio.c_cflag &= ~PARENB;
            break;
    }

    printf("Baund Rate: %d\n", nSpeed);

    switch( nSpeed )
    {
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
            break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
            break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
        case 115200:
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
            break;
        case 460800:
            cfsetispeed(&newtio, B460800);
            cfsetospeed(&newtio, B460800);
            break;
        case 921600:
            printf("Rate:921600\n");
            cfsetispeed(&newtio, B921600);
            cfsetospeed(&newtio, B921600);
            break;
        default:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
    }
    if( nStop == 1 )
        newtio.c_cflag &=  ~CSTOPB;
    else if ( nStop == 2 )
        newtio.c_cflag |=  CSTOPB;
    newtio.c_cc[VTIME]  = 0;
    newtio.c_cc[VMIN] = 0;
    
    tcflush(fd,TCIFLUSH);
    
    if((tcsetattr(fd,TCSANOW,&newtio))!=0)
    {
        perror("com set error");
        return -1;
    }
    printf("set done!\n\r");
    return 0;
}


int bsp_max485_init(void)
{
    int nset1,nread;

    int i = 0;

    char *max485_ctl = "/dev/max485_ctl_pin";

    max485_fd_ins = open("/dev/ttymxc2", O_RDWR|O_NOCTTY );
    if (max485_fd_ins < 0)
    {
        perror("open uart485 failed");
        return -1;
    }

    nset1 = set_opt(max485_fd_ins, 9600, 8, 'N', 1);
    
    if (nset1 == -1)
    {
        printf("Set uart faild\n");
        exit(1);
    }
    
    if(fcntl(max485_fd_ins, F_SETFL, 0) < 0)
        printf("fcntl failed!\n");
    else
        printf("fcntl=%d\n", fcntl(max485_fd_ins, F_SETFL, 0));
    
    if((max485_ctrl_fd_ins=open(max485_ctl, O_RDWR|O_NOCTTY|O_NDELAY))<0)
    {
        printf("Open %s faild\n", max485_ctl);
        close(max485_fd_ins);
        exit(1);
    }
    
    printf("max485 inited!\n");
}

int prepare_to_send(int fd)
{
    int ret;

    ret = ioctl(fd, 1, 0);  /* 1--high */
    if(ret<0)
    {
        printf("max485 set ctl to high failed!\r\n");

        return -1;
    }
    else
    {
        return 0;
    }
}

int prepare_to_recv(int fd)
{
    int ret;

    ret = ioctl(fd, 0, 0);  /* 1st0---low */
    if(ret<0)
    {
        printf("max485 set ctl to low failed!\r\n");
                
        return -1;
    }
    else
    {
        return 0;
    }
}

int bsp_max485_send(int max485_fd, const char* buffer, int size)
{
    int nread;
    /* prepare_to_send(max485_ctrl_fd_ins); */
    nread = write(max485_fd, buffer, size);
    return nread;
}


int bsp_max485_recv(int max485_fd,  char* buffer, int size)
{
    int nread = 0;
    int len = 0, ret = 0;
    fd_set fs_read;
    struct timeval tv_timeout;
    FD_ZERO(&fs_read);
    FD_SET(max485_fd, &fs_read);
    tv_timeout.tv_sec  = (10 * 20 / 9600 + 2);
    tv_timeout.tv_usec = 0;
    
    ret = select(max485_fd + 1, &fs_read, NULL, NULL, &tv_timeout);
    
    if (FD_ISSET(max485_fd, &fs_read))
    {
        /* prepare_to_recv(max485_ctrl_fd_ins); */
        nread = read(max485_fd, buffer, size);
        return nread;
    }
    
    
    return nread;
}


