cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(
    tsp
    VERSION 1.0.0
    DESCRIPTION "TSP Project"
    LANGUAGES CXX
)

include_directories(include)

file(GLOB SOURCES "src/*.cxx")

add_executable(
    tsp 
    "${SOURCES}"
)

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cxx")

add_library(tsp_lib STATIC "${SOURCES}")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TESTS "test/*.cxx")

add_executable(
    tests
    "${TESTS}"
)

target_link_libraries(
    tests
    tsp_lib
    GTest::gtest_main
)

set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

include(GoogleTest)
gtest_discover_tests(tests)