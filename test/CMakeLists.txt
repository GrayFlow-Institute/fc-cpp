cmake_minimum_required(VERSION 3.9)
project(Fc_Test)

#add_subdirectory(./lib/gtest)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(./lib/gtest)

aux_source_directory(. DIR)
aux_source_directory(fc FC)

add_executable(
    Fc_Test

    ${DIR}
    ${FC}
)

target_link_libraries(
    Fc_Test

    gtest
    gtest_main

    Fc
)