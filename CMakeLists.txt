#my great test using the cmake
#play it like play emacs
#EE:zhang 1054125296@qq.com
#copyright:
cmake_minimum_required(VERSION 3.10)

if(WIN32)
  message(STATUS "Windows is going on.")
elseif(UNIX)
  message(STATUS "linux is going on.")
  set(CMAKE_C_COMPILER  gcc)
  set(CMAKE_CXX_COMPILER g++)

  set(CMAKE_CC_FLAG "-g -Wall  ")
  set(CMAKE_CXX_FLAG "-g -Wall")
  set(CMAKE_BUILD_TYPE "Debug")
  set(CMAKE_COLOR_MAKEFILE ON)
endif(WIN32)


# set(CMAKE_OBJCOPY arm-none-eabi-objcopy) 
# set(CMAKE_SIZE arm-none-eabi-size)
# set(CMAKE_BUILD_TYPE "Release")
project(test)


include(${PROJECT_SOURCE_DIR}/cmake/app.cmake)

# 复用插件
include(${PROJECT_SOURCE_DIR}/cmake/extentions.cmake)

message("include extension cmake file")

if (${ARM_APP})
message("include arm header file")
  
include_directories(
  # ${PROJECT_SOURCE_DIR}/app
  ${PROJECT_SOURCE_DIR}/bsp/inc
  ${PROJECT_SOURCE_DIR}/flib/inc
  )
# lib directories
link_directories(
  ${PROJECT_BINARY_DIR}/lib
)

else()
message("include x86 header file")
  
#header files
include_directories(
  # ${PROJECT_SOURCE_DIR}/app
  ${PROJECT_SOURCE_DIR}/bsp/inc
  ${PROJECT_SOURCE_DIR}/flib/inc
  /usr/local/include
  /usr/include
  )
# lib directories
link_directories(
  ${PROJECT_BINARY_DIR}/lib
  /usr/local/lib
  /usr/lib
)  

endif (${ARM_APP})


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

if (${QT_APP})
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
  # 设置CMake在需要时自动运行moc
  set(CMAKE_AUTOMOC ON)
  # 从Qt设计师文件列表中创建代码
  set(CMAKE_AUTOUIC ON)

  set(CMAKE_AUTORCC ON)  
  set(CMAKE_PREFIX_PATH /opt/Qt/5.12.0/gcc_64/lib/cmake)
  # 寻找Qt5的库
  find_package(Qt5 COMPONENTS Widgets Gui Core REQUIRED)
else()
  

endif (${QT_APP})


add_subdirectory(app)  
add_subdirectory(bsp)
add_subdirectory(flib)
add_subdirectory(main)

configure_file(
  ${PROJECT_SOURCE_DIR}/main/app_config.h.in
  ${PROJECT_SOURCE_DIR}/main/app_config.h
  )











