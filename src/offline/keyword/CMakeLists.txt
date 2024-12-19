cmake_minimum_required(VERSION 3.16)
project(BuildKeyWord)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(${CMAKE_SOURCE_DIR}/utils/splitword SPLIT_WORD_SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/utils/base BASE_SRC_LIST)
aux_source_directory(. KEY_WORD_SRC_LIST)

add_executable(BuildKeyWord ${KEY_WORD_SRC_LIST} ${SPLIT_WORD_SRC_LIST} ${BASE_SRC_LIST} main.cpp)
target_link_libraries(BuildKeyWord pthread)
target_include_directories(BuildKeyWord PRIVATE
        ${CMAKE_SOURCE_DIR}/thirdpart
        ${CMAKE_SOURCE_DIR}
)