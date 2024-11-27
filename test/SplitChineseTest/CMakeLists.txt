include_directories(../../src/offline/keyword)

# 为 SplitChineseTest 创建测试
add_executable(SplitChineseTest ../../src/offline/keyword/SplitChinese.cpp
        ../../src/offline/keyword/JiebaSplitCn.cpp
        SplitChineseTest.cpp)
target_link_libraries(SplitChineseTest PRIVATE gtest_main gtest pthread)

# 注册测试
include(GoogleTest)
gtest_discover_tests(SplitChineseTest)



