file(GLOB hdrs "*.h")
file(GLOB srcs "*.c")

add_library(app_static STATIC  ${hdrs} ${srcs})

target_include_directories(app_static PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/function
  ${CMAKE_CURRENT_SOURCE_DIR}/intrrupts
)


