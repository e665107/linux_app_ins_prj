#!/bin/sh

PROJ=example
insmod ./$(PROJ).ko
dmesg | tail
mknod /dev/$(PROJ) c 60 0
chmod 666 /dev/$(PROJ)
echo -n "Happy!" > /dev/$(PROJ)
dmesg | tail
cat /dev/$(PROJ)
dmesg | tail
rm /dev/$(PROJ)
rmmod $(PROJ)
dmesg | tail
