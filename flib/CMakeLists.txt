if (${HELLO_WORLD_APP})
  set(SRCS
    src/delay.c
)
endif (${HELLO_WORLD_APP})


if (${UART_COMMUNICATION_APP})
  set(SRCS
    src/delay.c
)
endif (${UART_COMMUNICATION_APP})



add_library(flib_static STATIC  ${SRCS})


