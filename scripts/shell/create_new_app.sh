#!/bin/bash
   param=${2^^}
   sed -i 's/APP\ 1/APP 0/' ./cmake/app.cmake
   if [[ $2 =~ "qt" ]]
   then
       echo "create a qt app"		# create a qt app
       sed -i "/set(QT_HELLO_WORLD_APP 0)/a set("$param"_APP 1)" ./cmake/app.cmake
       sed -i 's/set(QT_APP\ 0)/set(QT_APP 1)/' ./cmake/app.cmake
   else
       echo "create a usual app"        	# create a normal app
       sed -i "/set(HELLO_WORLD_APP 0)/a set("$param"_APP 1)" ./cmake/app.cmake
   fi
   # exit 0
   cd app/
   sed -i '/endif\ (${HELLO_WORLD_APP})/a\if (${'"$param"'_APP})\
add_subdirectory('"$2"')\
endif (${'"$param"'_APP})\
' CMakeLists.txt
   sed -i '/endif\ (${HELLO_WORLD_APP})/G' CMakeLists.txt
   mkdir -p $2
   cp ./test_app/CMakeLists.txt  ./$2
   cp ./test_app/test_thread.c   ./$2
   cp ./test_app/test_thread.h   ./$2
   mv ./$2/test_thread.c ./$2/$2_thread.c
   mv ./$2/test_thread.h ./$2/$2_thread.h
   sed -i 's/TEST/'"$param"'/g' ./$2/$2_thread.h
   sed -i 's/test/'"$2"'/' ./$2/$2_thread.h
   sed -i 's/test_thread/'"$2"'_thread/' ./$2/$2_thread.c
   sed -i 's/Thread\ is/Thread_'"$2"' is/' ./$2/$2_thread.c
   if [[ $2 =~ "qt" ]]
   then

   fi
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
    create_'"$2"'_threads();\
#endif //'"$param"'_APP' app_init.c
   cd ../









