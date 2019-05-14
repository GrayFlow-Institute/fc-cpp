cmake_minimum_required(VERSION 3.9)
project(Fc_Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

aux_source_directory(. DIR)
aux_source_directory(fc FC)

include_directories(../src/fc/include)

add_executable(
    Fc_Test
    fc/main_test.cpp
    fc/test.cpp
)

target_link_libraries(
    Fc_Test
    ${GTEST_LIBRARIES}
)
