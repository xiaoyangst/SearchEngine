add_executable(CandidatePageTest
        CandidatePageTest.cpp
        ${CMAKE_SOURCE_DIR}/src/online/server/CandidatePage.cpp
)
target_link_libraries(CandidatePageTest PRIVATE gtest_main gtest log4cpp pthread)
target_include_directories(CandidatePageTest PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/)
# 注册测试
include(GoogleTest)
gtest_discover_tests(CandidatePageTest)

