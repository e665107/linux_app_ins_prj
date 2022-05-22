file(GLOB hdrs "*.h" "*.hpp" "lib/*.hpp")
file(GLOB srcs "*.c" "*.cpp" "lib/*.cpp")

# set(SRCS
#     hello_world_thread.h
#     hello_world_thread.c
# )

# add_executable(test_app main.cpp  ${hdrs} ${srcs} mainwindow.ui resources.qrc)
# find_package( Qt5Core )
# find_package( Qt5PrintSupport )
# find_package( Qt5Gui )
# find_package( Qt5Widgets )
add_library(app_static STATIC  ${hdrs} ${srcs} mainwindow.ui resources.qrc) 

target_include_directories(app_static PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(app_static  Qt5::Widgets Qt5::Core Qt5::Gui)

