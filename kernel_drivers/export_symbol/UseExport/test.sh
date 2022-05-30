#!/bin/sh

PROJ=useexample
insmod example.ko
insmod $PROJ.ko
cat /proc/kallsyms | grep hello1; echo
rmmod $PROJ
rmmod example

dmesg | tail -n 30
