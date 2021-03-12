#
# Print a message only if the `VERBOSE_OUTPUT` option is on
#

function(verbose_message content)
    if(${PROJECT_NAME}_VERBOSE_OUTPUT)
			message(STATUS ${content})
    endif()
endfunction()

#
# Add a target for formating the project using `clang-format` (i.e: cmake --build build --target clang-format)
#

function(add_clang_format_target)
    if(NOT ${PROJECT_NAME}_CLANG_FORMAT_BINARY)
			find_program(${PROJECT_NAME}_CLANG_FORMAT_BINARY clang-format)
    endif()

    if(${PROJECT_NAME}_CLANG_FORMAT_BINARY)
      if(${PROJECT_NAME}_BUILD_EXECUTABLE)
        foreach(f ${exe_sources})
          list(APPEND tmp "'${f}'")
          list(APPEND tmp "")
        endforeach()
      elseif(NOT ${PROJECT_NAME}_BUILD_HEADERS_ONLY)
        foreach(f ${sources})
          list(APPEND tmp "'${f}'")
          list(APPEND tmp "")
        endforeach()
      endif()

      if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
        foreach(f ${test_sources})
          list(APPEND tmp "'test/${f}'")
          list(APPEND tmp "")
        endforeach()
      endif()

      foreach(f ${headers})
        list(APPEND tmp "'${f}'")
        list(APPEND tmp "")
      endforeach()

      add_custom_target(clang-format
          COMMAND ${${PROJECT_NAME}_CLANG_FORMAT_BINARY} -i ${tmp}
          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

			message(STATUS "Format the project using the `clang-format` target (i.e: cmake --build build --target clang-format).\n")
    endif()
endfunction()
