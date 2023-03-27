add_library(${TARGET_NAME} cpp/example.cpp)

add_subdirectory(cpp)
#add_subdirectory(headers)
target_include_directories(${TARGET_NAME} PUBLIC headers)
target_include_directories(${TARGET_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
target_include_directories(${TARGET_NAME}
        PUBLIC
        headers
        )

# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(${TARGET_NAME}
    PUBLIC
      "--coverage"
    )
  target_link_options(${TARGET_NAME}
    INTERFACE
      "--coverage"
    )
endif()
