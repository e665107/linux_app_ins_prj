if (${HELLO_WORLD_APP})
add_subdirectory(hello_world)
endif (${HELLO_WORLD_APP})

if (${UART_COMMUNICATION_APP})
add_subdirectory(uart_communication)
endif (${UART_COMMUNICATION_APP})

if (${STRUCTURE_APP})
add_subdirectory(structures_and_algorithms)
endif (${STRUCTURE_APP})

if (${NET_COMMUNICATION_APP})
add_subdirectory(net_communication)
endif (${NET_COMMUNICATION_APP})

if (${HTTPD_APP})
add_subdirectory(httpd)
endif (${HTTPD_APP})

if (${HTTP_CLIENT_APP})
add_subdirectory(http_client)
endif (${HTTP_CLIENT_APP})


if (${QT_APP})
add_subdirectory(qt_apps)
endif (${QT_APP})
