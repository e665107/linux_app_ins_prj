#!/bin/sh


PROJ=example
insmod ./$PROJ.ko
cat /proc/kallsyms | grep $PROJ; echo
rmmod $PROJ
