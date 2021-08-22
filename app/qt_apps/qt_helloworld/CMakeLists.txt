file(GLOB hdrs "*.hpp" "lib/*.hpp")
file(GLOB srcs "*.cpp" "lib/*.cpp")

# set(SRCS
#     hello_world_thread.h
#     hello_world_thread.c
# )

add_executable(test_app main.cpp   ${hdrs} ${srcs} mainwindow.ui resources.qrc)

# add_library(app_static STATIC  ${hdrs} ${srcs} mainwindow.ui resources.qrc) 

# target_include_directories(app_static PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )

target_link_libraries(test_app  Qt5::Widgets Qt5::Core Qt5::Gui   )

