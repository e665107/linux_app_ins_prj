file(GLOB hdrs "*.h")
file(GLOB srcs "*.c")

# set(SRCS
#     hello_world_thread.h
#     hello_world_thread.c
# )
find_package(Libevent REQUIRED)

add_library(app_static STATIC  ${hdrs} ${srcs} )

target_link_libraries(app_static libevent.so)

target_include_directories(app_static PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR} 
)

