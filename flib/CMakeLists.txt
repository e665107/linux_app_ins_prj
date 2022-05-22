if (${HELLO_WORLD_APP})
  set(SRCS
    src/delay.c
)
endif (${HELLO_WORLD_APP})


if (${ENIC_APP})
  set(SRCS
    src/delay.c
)
endif (${ENIC_APP})

if (${CHAT_SERVER_APP})
  set(SRCS
    src/delay.c
)
endif (${CHAT_SERVER_APP})

if (${QT_HELLO_WORLD_APP})
  set(SRCS
    src/delay.c
)
endif (${QT_HELLO_WORLD_APP})

if (${UART_COMMUNICATION_APP})
  set(SRCS
    src/delay.c
)
endif (${UART_COMMUNICATION_APP})


if (${HTTPD_APP})
  set(SRCS
    src/delay.c
)
endif (${HTTPD_APP})

if (${HTTP_CLIENT_APP})
  set(SRCS
    src/delay.c
)
endif (${HTTP_CLIENT_APP})


add_library(flib_static STATIC  ${SRCS})


