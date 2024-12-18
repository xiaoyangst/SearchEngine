add_executable(CosineAlgorithmTest
        CosineAlgorithmTest.cpp
        ${CMAKE_SOURCE_DIR}/src/online/server/CosineAlgorithm.cpp
)
target_link_libraries(CosineAlgorithmTest PRIVATE gtest_main gtest log4cpp pthread)
target_include_directories(CosineAlgorithmTest PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/)
# 注册测试
include(GoogleTest)
gtest_discover_tests(CosineAlgorithmTest)

