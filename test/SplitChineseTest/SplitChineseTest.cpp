#include <gtest/gtest.h>
#include "../../src/offline/keyword/SplitChinese.h"

#if 0

TEST(SplitChineseRmStopWordsTests, HandlesEmptyString) {
    SplitChinese splitter("sources/project/stop/stop_words_zh.txt", "conf/jieba.json");
    std::string input = "";
    std::string result = splitter.rmStopWords(input);
    EXPECT_EQ(result, "");
}

TEST(SplitChineseRmStopWordsTests, HandlesStringWithNoStopWords) {
    SplitChinese splitter("sources/project/stop/stop_words_zh.txt", "conf/jieba.json");
    std::string input = "这是一个测试";
    std::string result = splitter.rmStopWords(input);
    EXPECT_EQ(result, "这是 一个 测试");
}

TEST(SplitChineseRmStopWordsTests, HandlesStringWithAllStopWords) {
    SplitChinese splitter("sources/project/stop/stop_words_zh.txt", "conf/jieba.json");
    splitter.m_stop_words.insert("这是");
    splitter.m_stop_words.insert("一个");
    std::string input = "这是一个测试";
    std::string result = splitter.rmStopWords(input);
    EXPECT_EQ(result, "测试");
}

TEST(SplitChineseRmStopWordsTests, HandlesStringWithSomeStopWords) {
    SplitChinese splitter("sources/project/stop/stop_words_zh.txt", "conf/jieba.json");
    splitter.m_stop_words.insert("一个");
    std::string input = "这是一个测试";
    std::string result = splitter.rmStopWords(input);
    EXPECT_EQ(result, "这是 测试");
}

TEST(SplitChineseRmStopWordsTests, HandlesStringWithMultipleSpaces) {
    SplitChinese splitter("sources/project/stop/stop_words_zh.txt", "conf/jieba.json");
    splitter.m_stop_words.insert("测试");
    std::string input = "这是   一个  测试";
    std::string result = splitter.rmStopWords(input);
    EXPECT_EQ(result, "这是 一个");
}

TEST(SplitChineseRmStopWordsTests, HandlesStringWithMixedStopWordsAndNonStopWords) {
    SplitChinese splitter("sources/project/stop/stop_words_zh.txt", "conf/jieba.json");
    splitter.m_stop_words.insert("这是");
    std::string input = "这是一个 非常 测试";
    std::string result = splitter.rmStopWords(input);
    EXPECT_EQ(result, "一个 非常 测试");
}

#endif