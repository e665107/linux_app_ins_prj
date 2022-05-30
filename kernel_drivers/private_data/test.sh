#!/bin/sh

PROJ=example
MAJORSCRIPT=`dmesg | grep "EXAMPLE: $(PROJ) driver(major [0-9]\+) installed" | tail -n 1 | sed -n 's/.*major \(.*\)).*/\1/p'`

insmod ./$PROJ.ko
dmesg | tail
mknod /dev/$(PROJ) c $(MAJORSCRIPT) 0
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

rm /dev/$(PROJ)
rmmod $(PROJ)
dmesg | tail

