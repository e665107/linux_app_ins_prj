#!/bin/bash 
#Filename: auto.sh

if [ "$1" = "app" ];then
   # param=${2^^}
   # sed -i "/set(HELLO_WORLD_APP 0)/a set("$param"_APP 1)" ./cmake/app.cmake
   # cd app/
   # sed -i '/endif\ (${HELLO_WORLD_APP})/a\if (${'"$param"'_APP})' CMakeLists.txt
   # sed -i '/if\ (${'"$param"'_APP})/a add_subdirectory('"$2"')' CMakeLists.txt
   # sed -i '/add_subdirectory('"$2"')/a endif (${'"$param"'_APP})' CMakeLists.txt
   # sed -i '/endif\ (${HELLO_WORLD_APP})/G' CMakeLists.txt
   # mkdir -p $2
   # cp ./hello_world/CMakeLists.txt ./$2
   # cd ../bsp
   source ./scripts/shell/create_new_app.sh
fi
   
if [ "$1" = "clean" ];then
    rm -r build
    # make clean    
    # rm CMakeCache.txt   
    # rm -r CMakeFiles
    # rm -r */CMakeFiles
    mkdir build
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

