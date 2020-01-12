# include_directories(${PROJECT_SOURCE_DIR}/app)

file(GLOB hdrs "*.h")
file(GLOB srcs "*.c")
file(GLOB mainfile "main.c")
list(REMOVE_ITEM srcs ${mainfile})


# add_library(cli_objs OBJECT ${hdrs} ${srcs} )

# add_executable(test ${hdrs} ${mainfile}  $<TARGET_OBJECTS:cli_objs>)

#link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(test_app ${srcs} ${hdrs} ${mainfile})

# target_link_libraries(test_app app_static  bsp_static comlib_static pthread )

target_link_libraries(test_app  flib_static bsp_static app_static pthread)


