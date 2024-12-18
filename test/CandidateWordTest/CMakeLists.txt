# 为 CandidateWordTest 创建测试
add_executable(CandidateWordTest
        CandidateWordTest.cpp
        ${CMAKE_SOURCE_DIR}/src/online/server/CandidateWord.cpp
)
target_link_libraries(CandidateWordTest PRIVATE gtest_main gtest log4cpp pthread)
target_include_directories(CandidateWordTest PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/)
# 注册测试
include(GoogleTest)
gtest_discover_tests(CandidateWordTest)

