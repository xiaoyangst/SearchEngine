add_executable(EditDistanceTest
        EditDistanceTest.cpp
        ${CMAKE_SOURCE_DIR}/src/online/server/EditDistance.cpp
)
target_link_libraries(EditDistanceTest PRIVATE gtest_main gtest log4cpp pthread)
target_include_directories(EditDistanceTest PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/)
# 注册测试
include(GoogleTest)
gtest_discover_tests(EditDistanceTest)