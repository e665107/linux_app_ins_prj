#!/bin/sh
#Filename: auto.sh

if [ "$1" = "clean" ];then
    cd build
    make clean    
    rm CMakeCache.txt   
    rm -r CMakeFiles
    rm -r */CMakeFiles
    echo  "cleaned"    
fi

if [ "$1" = "" ];then
    cd  build
    cmake  -G "Unix Makefiles" ../
    make
    echo "comiled done"
fi

if [ "$1" = "run" ];then
    ./build/bin/test_app
    echo "executed done"
fi

if [ "$1" = "gdb" ];then
    gdb ./build/bin/test_app
    echo "executed done"
fi


