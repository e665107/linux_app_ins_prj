#include "bsp_buzz.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int buzz_fd;

void bsp_buzz_init()
{
    buzz_fd = open("/dev/buzzer_ctl", 0);
    if(buzz_fd<0)
    {
        perror("open device buzz faibuzz!");
        exit(1);
    }

}


void bsp_buzz_on(int fd)
{

    ioctl(fd,1,0);

}

void bsp_buzz_off(int fd)
{

    ioctl(fd,0,0);
}

void buzz_toggle(int fd)
{
    static int BUZZ = 0;
    BUZZ=~BUZZ;
    if(BUZZ==0)
    {
        ioctl(fd,1,0);
    }
    else
    {
        ioctl(fd,0,0);
    }
}
