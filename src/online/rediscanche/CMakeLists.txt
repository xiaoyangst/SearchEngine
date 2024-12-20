cmake_minimum_required(VERSION 3.16)
project(BuildRedisCache)

set(CMAKE_CXX_STANDARD 20)


aux_source_directory(. REDIS_SERVER_SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/utils/base REDIS_BASE_SRC_LIST)

add_executable(BuildRedisCache ${REDIS_SERVER_SRC_LIST} ${REDIS_BASE_SRC_LIST} main.cpp)
target_link_libraries(BuildRedisCache log4cpp hv redis++ hiredis pthread)
target_include_directories(BuildRedisCache PRIVATE
        ${CMAKE_SOURCE_DIR}/thirdpart
        ${CMAKE_SOURCE_DIR}
)