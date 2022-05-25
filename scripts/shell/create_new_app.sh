#!/bin/bash
   param=${2^^}
   sed -i "/set(HELLO_WORLD_APP 0)/a set("$param"_APP 1)" ./cmake/app.cmake
   cd app/
   sed -i '/endif\ (${HELLO_WORLD_APP})/a\if (${'"$param"'_APP})\
add_subdirectory('"$2"')\
endif (${'"$param"'_APP})\
' CMakeLists.txt
   sed -i '/endif\ (${HELLO_WORLD_APP})/G' CMakeLists.txt
   mkdir -p $2
   cp ./hello_world/CMakeLists.txt ./$2
   # add app sources
   cd ../bsp
   sed -i '/endif\ (${HELLO_WORLD_APP})/a\if (${'"$param"'_APP})\
set(SRCS src/bsp_ttyusb0.c)\
endif (\${'"$param"'_APP})' CMakeLists.txt
   sed -i '/endif\ (${HELLO_WORLD_APP})/G' CMakeLists.txt
   cd ../flib
   sed -i '/endif\ (${HELLO_WORLD_APP})/a\if (${'"$param"'_APP})\
set(SRCS src/delay.c)\
endif (${'"$param"'_APP})' CMakeLists.txt
   sed -i '/endif\ (${HELLO_WORLD_APP})/G' CMakeLists.txt
   cd ../main
   sed -i '/#cmakedefine\  HELLO_WORLD_APP/a\#cmakedefine\  '"$param"'_APP' app_config.h.in
   sed -i '/#endif\ \/\/HELLO_WORLD_APP/a\#ifdef '"$param"'_APP\
#include \"'"$2"'_thread.h\"\
#endif //'"$param"'_APP' app_init.c
   sed -i '/#endif\ \/\/ HELLO_WORLD_APP/a\#ifdef '"$param"'_APP\
    create_'"$2"'_thread();\
#endif //'"$param"'_APP' app_init.c
   cd ../

