cmake_minimum_required(VERSION 3.16)
project(BuildServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
aux_source_directory(. SERVER_SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/utils/base BASE_SRC_LIST)

add_executable(BuildServer ${SERVER_SRC_LIST} ${BASE_SRC_LIST} main.cpp)
target_link_libraries(BuildServer log4cpp pthread hv)
target_include_directories(BuildServer PRIVATE
        ${CMAKE_SOURCE_DIR}/thirdpart
        ${CMAKE_SOURCE_DIR}
)