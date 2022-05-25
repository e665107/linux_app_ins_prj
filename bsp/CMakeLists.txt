if (${HELLO_WORLD_APP})
  set(SRCS
    src/bsp_ttyusb0.c
)
endif (${HELLO_WORLD_APP})

if (${TEST9_APP})
set(SRCS src/bsp_ttyusb0.c)
endif (${TEST9_APP})

if (${TEST8_APP})
set(SRCS src/bsp_ttyusb0.c)
endif (${TEST8_APP})

if (${TEST7_APP})
set(SRCS src/bsp_ttyusb0.c)
endif (${TEST7_APP})


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
