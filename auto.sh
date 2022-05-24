#!/bin/bash 
#Filename: auto.sh

if [ "$1" = "app" ];then
   param=${2^^}
   sed -i "/set(HELLO_WORLD_APP 0)/a set("$param"_APP 1)" ./cmake/app.cmake
   cd app/
   sed -i "/endif (${HELLO_WORLD_APP})/a 
if (\${"$param"_APP}) 
add_subdirectory($2) 
endif (\${"$param"_APP}) 
" CMakeLists.txt

   # cd app
   # mkdir -p $2
   
fi

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

