if (${HELLO_WORLD_APP})
  set(SRCS
    src/bsp_ttys0.c
)
endif (${HELLO_WORLD_APP})

if (${UART_COMMUNICATION_APP})
set(SRCS
    src/bsp_ttyusb0.c
)
endif (${UART_COMMUNICATION_APP})

add_library(bsp_static STATIC  ${SRCS})
