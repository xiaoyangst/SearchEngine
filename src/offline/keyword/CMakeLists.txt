cmake_minimum_required(VERSION 3.16)
project(BuildKeyWord)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(. KEY_WORD_SRC_LIST)

add_executable(BuildKeyWord ${KEY_WORD_SRC_LIST} main.cpp)
target_link_libraries(BuildKeyWord)