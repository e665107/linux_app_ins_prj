#include "bsp_led.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int led_fd;

void bsp_led_init()
{
    led_fd = open("/dev/leds_ctl", 0);
    if(led_fd<0)
    {
        perror("open device led failed!");
        exit(1);
    }

}


void bsp_led_on(int fd)
{

    ioctl(fd,1,0);

}

void bsp_led_off(int fd)
{

    ioctl(fd,0,0);
}

void led_toggle(int fd)
{
    static int LED = 0;
    LED=~LED;
    if(LED==0)
    {
        ioctl(fd,1,0);
    }
    else
    {
        ioctl(fd,0,0);
    }
}
