
# https://cmake.org/cmake/help/latest/command/target_include_directories.html
function(flower_include_directories)
  foreach(arg ${ARGV})
    if(IS_ABSOLUTE ${arg})
      set(path ${arg})
    else()
      set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
    endif()
    target_include_directories(flower_interface INTERFACE ${path})
  endforeach()
endfunction()
 

function(flower_link_interface interface)
  target_link_libraries(${interface} INTERFACE flower_interface)
endfunction()

 
