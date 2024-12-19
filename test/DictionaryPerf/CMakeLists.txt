cmake_minimum_required(VERSION 3.16)
project(DictionaryPerf)


aux_source_directory(${CMAKE_SOURCE_DIR}/utils/base baseSRc)
add_executable(DictionaryPerf
        DictionaryPerf.cpp
        ${CMAKE_SOURCE_DIR}/src/offline/keyword/Dictionary.cpp
        ${CMAKE_SOURCE_DIR}/utils/splitword/SplitEnglish.cpp
        ${CMAKE_SOURCE_DIR}/utils/splitword/SplitTool.cpp
        ${baseSRc}
)
target_link_libraries(DictionaryPerf PRIVATE benchmark pthread)
target_include_directories(DictionaryPerf PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/)