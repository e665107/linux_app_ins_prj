#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>

void Delay(uint32_t nTime);

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
					 
#define ARRAYSIZE(x) (sizeof(x)/sizeof((x)[0]))

#define HIGH32(x) ((uint32_t)(((uint64_t)x) >> 32) & 0xffffffff)
#define LOW32(x) (((uint64_t)x)  & 0xffffffff)

#define PP_HTONS(x) ((uint16_t)((((x) & (uint16_t)0x00ffU) << 8) | (((x) & (uint16_t)0xff00U) >> 8)))
#define PP_NTOHS(x) PP_HTONS(x)
#define PP_HTONL(x) ((((x) & (uint32_t)0x000000ffUL) << 24) | \
                     (((x) & (uint32_t)0x0000ff00UL) <<  8) | \
                     (((x) & (uint32_t)0x00ff0000UL) >>  8) | \
                     (((x) & (uint32_t)0xff000000UL) >> 24))
#define PP_NTOHL(x) PP_HTONL(x)

#ifndef read32
#define read32(addr)        (*(volatile uint32_t *)((uint64_t)addr))
#endif

#ifndef write32
#define write32(addr, val)  (*(volatile uint32_t *)((uint64_t)addr) = (val))
#endif

#define __packed        __attribute__((packed))
#define __align4        __attribute__((aligned(4)))
#define __init          __attribute__((section(".init.text")))
#define __exdata        __attribute__((section(".exdata")))

#define HIGH_LEVEL   1
/* print */
#define print(level, ...) \
    if (level >= HIGH_LEVEL) { \
        printf(__VA_ARGS__);   \
    }   
#endif /* _COMMON_H */
