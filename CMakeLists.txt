cmake_minimum_required(VERSION 3.16)
project(SearchEngine)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
find_package(GTest REQUIRED)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
aux_source_directory(utils/base BASE_MAIN_SRC)
add_executable(SearchEngine main.cpp ${BASE_MAIN_SRC})
target_link_libraries(SearchEngine pthread)
