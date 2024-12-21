cmake_minimum_required(VERSION 3.16)
project(BuildExclusiveLRU)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

aux_source_directory(. EXCLUSIVE_LRU_SERVER_SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/utils/base EXCLUSIVE_LRU_BASE_SRC_LIST)

add_executable(BuildExclusiveLRU ${EXCLUSIVE_LRU_SERVER_SRC_LIST} ${EXCLUSIVE_LRU_BASE_SRC_LIST} main.cpp)
target_link_libraries(BuildExclusiveLRU log4cpp hv pthread)
target_include_directories(BuildExclusiveLRU PRIVATE
        ${CMAKE_SOURCE_DIR}/thirdpart
        ${CMAKE_SOURCE_DIR}
)