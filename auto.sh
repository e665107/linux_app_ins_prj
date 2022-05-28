#!/bin/bash 
#Filename: auto.sh

if [ "$1" = "app" ];then
   source ./scripts/shell/create_new_app.sh
fi
   
if [ "$1" = "clean" ];then
    rm -r build
    mkdir build
    echo  "cleaned"    
fi

if [ "$1" = "arm" ];then
    cd  build
    cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/arm_linux_cross.cmake ..
    make -j4
    echo "comiled done"
fi

if [ "$1" = "riscv" ];then
    cd  build
    cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/riscv_linux_cross.cmake ..
    make -j4
    echo "comiled done"
fi


if [ "$1" = "" ];then
    cd  build
    cmake  -G "Unix Makefiles" ../
    make -j4
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

