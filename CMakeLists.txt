cmake_minimum_required(VERSION 3.16)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)

add_executable(SearchEngine main.cpp)
