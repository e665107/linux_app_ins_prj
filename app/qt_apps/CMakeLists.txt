# qt apps 
set(QT_HELLO_WORLD_APP 1)
set(QT_STRUCTURE_APP 0)
set(QT_UART_COMMUNICATION_APP 0)
set(QT_QT_APP 0)

if (${QT_HELLO_WORLD_APP})
add_subdirectory(qt_helloworld)
endif (${QT_HELLO_WORLD_APP})

# add_executable(test_app main.cpp  )

# target_link_libraries(test_app  Qt5::Widgets Qt5::Core Qt5::Gui  app_static)

# target_link_libraries(test_app  Qt5::Widgets Qt5::Core Qt5::Gui  app_static)

