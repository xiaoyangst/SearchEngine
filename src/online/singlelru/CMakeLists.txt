cmake_minimum_required(VERSION 3.16)
project(BuildSingleLRU)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

aux_source_directory(. SINGLE_LRU_SERVER_SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/utils/base SINGLE_LRU_BASE_SRC_LIST)

add_executable(BuildSingleLRU ${SINGLE_LRU_SERVER_SRC_LIST} ${SINGLE_LRU_BASE_SRC_LIST} main.cpp)
target_link_libraries(BuildSingleLRU log4cpp hv pthread)
target_include_directories(BuildSingleLRU PRIVATE
        ${CMAKE_SOURCE_DIR}/thirdpart
        ${CMAKE_SOURCE_DIR}
)