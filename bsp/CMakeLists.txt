if (${HELLO_WORLD_APP})
  set(SRCS
    src/bsp_ttyusb0.c
)
endif (${HELLO_WORLD_APP})

if (${CODING_FRAME_APP})
  set(SRCS
  src/bsp_max485.c
  src/bsp_led.c
  src/bsp_buzz.c
	)
endif (${CODING_FRAME_APP})

if (${QT_TEST1_APP})
set(SRCS src/bsp_ttyusb0.c)
endif (${QT_TEST1_APP})

if (${HAPPY_HACK1_APP})
set(SRCS src/bsp_ttyusb0.c)
endif (${HAPPY_HACK1_APP})

if (${HAPPY_HACK_APP})
set(SRCS src/bsp_ttyusb0.c)
endif (${HAPPY_HACK_APP})

if (${QT_TST1_APP})
set(SRCS src/bsp_ttyusb0.c)
endif (${QT_TST1_APP})

if (${TEST1_APP})
set(SRCS src/bsp_ttyusb0.c)
endif (${TEST1_APP})


if (${UART_COMMUNICATION_APP})
set(SRCS
    src/bsp_ttyusb0.c
)
endif (${UART_COMMUNICATION_APP})

if (${ENIC_APP})
set(SRCS
    src/bsp_ttyusb0.c
)
endif (${ENIC_APP})

if (${QT_HELLO_WORLD_APP})
set(SRCS
    src/bsp_ttyusb0.c
)
endif (${QT_HELLO_WORLD_APP})

if (${CHAT_SERVER_APP})
set(SRCS
    src/bsp_ttyusb0.c
)
endif (${CHAT_SERVER_APP})

if (${MYSQL_ACCESS_APP})
set(SRCS
    src/bsp_ttyusb0.c
)
endif (${MYSQL_ACCESS_APP})


if (${HTTPD_APP})
  set(SRCS
    src/bsp_ttyusb0.c
)
endif (${HTTPD_APP})

if (${HTTP_CLIENT_APP})
 set(SRCS
    src/bsp_ttyusb0.c
)
endif (${HTTP_CLIENT_APP})


add_library(bsp_static STATIC  ${SRCS})

target_include_directories(bsp_static PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}/c-periphery/src 
)
