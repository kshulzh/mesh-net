include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

add_executable(
    unit_tests
        containers/list.cpp
        io/readers/reader.cpp
        io/writers/writers.cpp
        io/connection/mock_radar.cpp
        io/connection/mock_connection.cpp
        services/connection/tests.cpp
        services/route/tests.cpp
        model/instance.cpp
        model/graph.cpp
)

target_link_libraries(unit_tests
  PRIVATE
    ${TARGET_NAME}
    ${TARGET_NAME_TEST}
    gtest_main
  )

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(unit_tests
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
  )
