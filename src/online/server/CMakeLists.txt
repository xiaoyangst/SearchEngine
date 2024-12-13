cmake_minimum_required(VERSION 3.16)
project(BuildServer)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(. SERVER_SRC_LIST)

add_executable(BuildServer ${SERVER_SRC_LIST} main.cpp)
target_link_libraries(BuildServer log4cpp pthread)
target_include_directories(BuildServer PRIVATE
    ${CMAKE_SOURCE_DIR}/thirdpart
    ${CMAKE_SOURCE_DIR}
)