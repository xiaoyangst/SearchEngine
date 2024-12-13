cmake_minimum_required(VERSION 3.16)
project(BuildClient)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(. CLIENT_SRC_LIST)

add_executable(BuildClient ${CLIENT_SRC_LIST} main.cpp)