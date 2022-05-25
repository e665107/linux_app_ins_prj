file(GLOB hdrs "*.h" "*.hpp" )
file(GLOB srcs "*.c" "*.cpp" )

# set(SRCS
#     hello_world_thread.h
#     hello_world_thread.c
# )

add_library(app_static STATIC  ${hdrs} ${srcs})

target_include_directories(app_static PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}  
)


