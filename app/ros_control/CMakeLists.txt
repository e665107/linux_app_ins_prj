file(GLOB hdrs "*.h" "*.hpp" "lib/*.h")
file(GLOB srcs "*.c" "*.cpp" "lib/*.c")

# set(SRCS
#     hello_world_thread.h
#     hello_world_thread.c
# )

add_library(app_static STATIC  ${hdrs} ${srcs})

target_include_directories(app_static PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}  ${CMAKE_CURRENT_SOURCE_DIR}/lib 
)


