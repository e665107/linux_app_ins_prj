file(GLOB hdrs "*.h")
file(GLOB srcs "*.c")

# set(SRCS
#     hello_world_thread.h
#     hello_world_thread.c
# )
  
add_library(my_lib_static STATIC  ${hdrs} ${srcs})

target_include_directories(my_lib_static PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

