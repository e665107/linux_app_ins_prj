if (${HELLO_WORLD_APP})
  set(SRCS
    src/delay.c
)
endif (${HELLO_WORLD_APP})

if (${CODING_FRAME_APP})

endif (${CODING_FRAME_APP})

if (${QT_TEST1_APP})
set(SRCS src/delay.c)
endif (${QT_TEST1_APP})

if (${HAPPY_HACK1_APP})
set(SRCS src/delay.c)
endif (${HAPPY_HACK1_APP})

if (${HAPPY_HACK_APP})
set(SRCS src/delay.c)
endif (${HAPPY_HACK_APP})

if (${QT_TST1_APP})
set(SRCS src/delay.c)
endif (${QT_TST1_APP})

if (${TEST1_APP})
set(SRCS src/delay.c)
endif (${TEST1_APP})


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

if (${MYSQL_ACCESS_APP})
  set(SRCS
    src/delay.c
)
endif (${MYSQL_ACCESS_APP})

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

set(SRCS
    src/thread_common.c
    src/delay.c
)

add_library(flib_static STATIC  ${SRCS})





