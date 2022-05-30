#!/bin/sh

PROJ=example
insmod ./$(PROJ).ko
dmesg | tail
cat /sys/class/$(PROJ)/$(PROJ)/dev
cat /sys/class/$(PROJ)/$(PROJ)/uevent
chmod 666 /dev/$(PROJ)
ls -l /dev/$(PROJ)

cat /dev/$(PROJ)
dmesg | tail -n 40
echo Happy! > /dev/$(PROJ)
dmesg | tail -n 40
cat /dev/$(PROJ)
dmesg | tail -n 40
#echo GoGoGoGoGoGo! > /dev/$(PROJ)
#dmesg | tail -n 40
#cat /dev/$(PROJ)
#dmesg | tail -n 40

rmmod $(PROJ)
dmesg | tail

