add_library(bsp_static STATIC  ${SRCS})

target_include_directories(bsp_static PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
