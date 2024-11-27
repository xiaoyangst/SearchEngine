include_directories(../../src/offline/keyword)

add_executable(SplitEnglishTest ../../src/offline/keyword/SplitEnglish.cpp SplitEnglishTest.cpp)
target_link_libraries(SplitEnglishTest PRIVATE gtest_main gtest pthread)

# 注册测试
include(GoogleTest)
gtest_discover_tests(SplitEnglishTest)