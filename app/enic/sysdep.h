#ifndef __SYSDEP_H__
#define __SYSDEP_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__linux__) && defined (__KERNEL__)

/* Linux kernel mode */
#include <linux/kernel.h>
#include <linux/types.h>

#elif defined (__FreeBSD__) && defined (_KERNEL)

/* FreeBSD kernel mode */
#include <sys/types.h>
#include <sys/param.h>
#include <sys/kernel.h>

#elif defined (_WIN64) && defined (KERNEL_SPACE)

/* Windows kernel mode */
#include <ntddk.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#elif defined (__linux__) || defined (__FreeBSD__) || defined (WIN32) || defined (_WIN64) 
/* Linux, FreeBSD, or Windows user mode */
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#elif defined (_WRS_KERNEL)

/* Wind River VxWorks kernel mode */
#include <types/vxTypes.h>

#else
/* TIH baremetal mode */
#include <stdint.h>

#endif /* OS and mode */

#if defined (WIN32) || defined (_WIN64)
/* nonstandard extension used : zero-sized array in struct/union */
#pragma warning (disable: 4200)
#endif

/*****************************************************************************
 *      Generic Base Data Type definitions
 *****************************************************************************/
#ifndef NULL
#define NULL               (0)
#endif

#ifndef TRUE
#define TRUE               (1==1)

#endif
#ifndef FALSE
#define FALSE              (0==1)
#endif

#ifndef DIR_IN
#define DIR_IN             (0)
#endif

#ifndef DIR_OUT
#define DIR_OUT            (1)
#endif

#ifndef ADDR_INC
#define ADDR_INC           (0)
#endif

#ifndef ADDR_FIX
#define ADDR_FIX           (1)
#endif

/* #ifndef ENABLE */
/* #define ENABLE             (1) */
/* #endif */

/* #ifndef DISABLE */
/* #define DISABLE            (0) */
/* #endif */

#ifndef bool
typedef int bool;
#endif

#ifndef read64
#define read64(addr)        (*(volatile uint64_t *)((uint64_t)addr))
#endif

#ifndef read32
#define read32(addr)        (*(volatile uint32_t *)((uint64_t)addr))
#endif

#ifndef read16
#define read16(addr)        (*(volatile uint16_t *)((uint64_t)addr))
#endif

#ifndef read8
#define read8(addr)         (*(volatile uint8_t *)((uint64_t)addr))
#endif

#ifndef write64
#define write64(addr, val)  (*(volatile uint64_t *)((uint64_t)addr) = (val))
#endif

#ifndef write32
#define write32(addr, val)  (*(volatile uint32_t *)((uint64_t)addr) = (val))
#endif

#ifndef write16
#define write16(addr, val)  (*(volatile uint16_t *)((uint64_t)addr) = (val))
#endif

#ifndef write8
#define write8(addr, val)   (*(volatile uint8_t *)((uint64_t)addr) = (val))
#endif

#define __exdata        __attribute__((section(".exdata"),zero_init))

#ifdef __cplusplus
} /* close the extern "C" { */
#endif

#endif 












