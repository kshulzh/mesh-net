add_library(${TARGET_NAME}
)

SET_TARGET_PROPERTIES( ${TARGET_NAME}
        PROPERTIES
        LINKER_LANGUAGE C
        )
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qc <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_C_ARCHIVE_FINISH "<CMAKE_RANLIB> <TARGET>")
set(CMAKE_C_COMPILE_OBJECT
        "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")
#add_subdirectory(headers)
add_subdirectory(c)
target_include_directories(${TARGET_NAME} PUBLIC headers)
target_include_directories(${TARGET_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
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
