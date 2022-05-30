#ifndef __TEST_IOCTL_H__
#define __TEST_IOCTL_H__

#include <linux/ioctl.h>

#define IOC_MAGIC '\x66'

/* IO control actions. */
#define	IOCTL_CMD_0_FLAG	(_IO(IOC_MAGIC,  0, int))
#define	IOCTL_GET_FLAG	        (_IOR(IOC_MAGIC, 1, int))
#define	IOCTL_SET_FLAG	        (_IOW(IOC_MAGIC, 2, int))




#endif
