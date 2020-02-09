if (${HELLO_WORLD_APP})
  set(SRCS
    src/bsp_ttyusb0.c
)
endif (${HELLO_WORLD_APP})

if (${UART_COMMUNICATION_APP})
set(SRCS
    src/bsp_ttyusb0.c
)
endif (${UART_COMMUNICATION_APP})


add_library(bsp_static STATIC  ${SRCS})

target_include_directories(bsp_static PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}/c-periphery/src 
)
