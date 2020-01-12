#include "delay.h" 

void delay_ms(int ms)
{
    int  i;
    for(; ms != 0; ms--)
        for(i=8000;i!=0;i--);
}
