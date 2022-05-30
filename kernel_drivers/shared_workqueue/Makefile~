PROJ=dedicated-workqueue
KERN_DIR=/home/e66/imx/linux_imx_new/kernel_imx/

CROSS=/home/e66/imx/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-

obj-m+=$(PROJ).o

ifeq ($(KERNELDIR),)
KERNELDIR=/lib/modules/$(shell uname -r)/build
endif


all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERN_DIR) M=$(shell pwd) modules 

clean:
	make -C $(KERN_DIR) M=$(shell pwd)  clean
	rm -rf modules.order



