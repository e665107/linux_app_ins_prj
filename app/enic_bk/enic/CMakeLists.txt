file(GLOB hdrs "*.h" "*.hpp" )
file(GLOB srcs "*.c" "*.cpp" )

option(USE_TEST "debug mode" ON)

# select to use debug mode, or common function
message("USE_TEST is ${USE_TEST}")
if(USE_TEST)
  add_definitions(-DTEST)
  message("MACRO TEST is DEFINED")
  add_definitions(-DDEBUG)
  message("MACRO DEBUG is DEFINED")
else()
endif(USE_TEST)

add_library(app_static STATIC  ${hdrs} ${srcs})

target_include_directories(app_static PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}  
)


