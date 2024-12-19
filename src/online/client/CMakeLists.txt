cmake_minimum_required(VERSION 3.16)
project(BuildClient)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(. CLIENT_SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/utils/base BASE_SRC_LIST)

add_executable(BuildClient ${CLIENT_SRC_LIST} ${BASE_SRC_LIST} main.cpp)
target_link_libraries(BuildClient hv pthread)
target_include_directories(BuildClient PRIVATE
    ${CMAKE_SOURCE_DIR}/thirdpart
    ${CMAKE_SOURCE_DIR}
)