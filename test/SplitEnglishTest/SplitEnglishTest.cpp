#include <gtest/gtest.h>
#include "../../src/offline/keyword/SplitEnglish.h"


/*
 * rinse 测试
*/

#if 0

TEST(SplitEnglishRinseTests, HandlesEmptyString
) {
  SplitEnglish splitter("");
  std::string input = "";
  splitter.rinse(input);
  EXPECT_EQ(input,
            "");
}

TEST(SplitEnglishRinseTests, HandlesStringWithOnlyLettersAndNumbers
) {
  SplitEnglish splitter("");
  std::string input = "abc123XYZ";
  splitter.rinse(input);
  EXPECT_EQ(input,
            "abc123xyz");
}

TEST(SplitEnglishRinseTests, HandlesStringWithPunctuation
) {
  SplitEnglish splitter("");
  std::string input = "Hello, World! 123";
  splitter.rinse(input);
  EXPECT_EQ(input,
            "hello  world  123");
}

TEST(SplitEnglishRinseTests, HandlesStringWithSpaces
) {
  SplitEnglish splitter("");
  std::string input = "    ";
  splitter.rinse(input);
  EXPECT_EQ(input,
            "    ");
}

TEST(SplitEnglishRinseTests, HandlesStringWithOnlySpecialCharacters
) {
  SplitEnglish splitter("");
  std::string input = "!@#$%^&*()";
  splitter.rinse(input);
  EXPECT_EQ(input,
            "          ");
}

TEST(SplitEnglishRinseTests, HandlesStringWithMixedCaseAndDigits
) {
  SplitEnglish splitter("");
  std::string input = "ABcd1234EFGH";
  splitter.rinse(input);
  EXPECT_EQ(input,
            "abcd1234efgh");
}

TEST(SplitEnglishRinseTests, HandlesStringWithLeadingAndTrailingSpaces
) {
  SplitEnglish splitter("");
  std::string input = "   abc123   ";
  splitter.rinse(input);
  EXPECT_EQ(input,
            "   abc123   ");
}
#endif

/*
 * rmStopWords 测试
*/

#if 0

TEST(SplitEnglishRmStopWordsTests, HandlesEmptyString) {
  SplitEnglish splitter("");
  std::string input = "";
  std::string result = splitter.rmStopWords(input);
  EXPECT_EQ(result, "");
}

TEST(SplitEnglishRmStopWordsTests, HandlesStringWithNoStopWords) {
  SplitEnglish splitter("");
  std::string input = "this is a test";
  splitter.m_stop_words.insert("is");
  splitter.m_stop_words.insert("a");
  std::string result = splitter.rmStopWords(input);
  EXPECT_EQ(result, "this test");
}

TEST(SplitEnglishRmStopWordsTests, HandlesStringWithAllStopWords) {
  SplitEnglish splitter("");
  std::string input = "this is a test";
  splitter.m_stop_words.insert("this");
  splitter.m_stop_words.insert("is");
  splitter.m_stop_words.insert("a");
  splitter.m_stop_words.insert("test");
  std::string result = splitter.rmStopWords(input);
  EXPECT_EQ(result, "");
}

TEST(SplitEnglishRmStopWordsTests, HandlesStringWithNoStopWordsFound) {
  SplitEnglish splitter("");
  std::string input = "hello world";
  splitter.m_stop_words.insert("is");
  splitter.m_stop_words.insert("a");
  std::string result = splitter.rmStopWords(input);
  EXPECT_EQ(result, "hello world");
}

TEST(SplitEnglishRmStopWordsTests, HandlesStringWithMultipleSpaces) {
  SplitEnglish splitter("");
  std::string input = "hello    world";
  splitter.m_stop_words.insert("world");
  std::string result = splitter.rmStopWords(input);
  EXPECT_EQ(result, "hello");
}

TEST(SplitEnglishRmStopWordsTests, HandlesStringWithMixedCaseStopWords) {
  SplitEnglish splitter("");
  std::string input = "This is A test";
  splitter.m_stop_words.insert("is");
  splitter.m_stop_words.insert("a");
  std::string result = splitter.rmStopWords(input);
  EXPECT_EQ(result, "this test");
}

#endif

/*
 * toLower 测试
 */

#if 0

TEST(SplitEnglishToLowerTests, HandlesEmptyString) {
  SplitEnglish splitter("");
  std::string input = "";
  std::string result = splitter.toLower(input);
  EXPECT_EQ(result, "");
}

TEST(SplitEnglishToLowerTests, HandlesStringWithAllLowercaseLetters) {
  SplitEnglish splitter("");
  std::string input = "hello";
  std::string result = splitter.toLower(input);
  EXPECT_EQ(result, "hello");
}

TEST(SplitEnglishToLowerTests, HandlesStringWithAllUppercaseLetters) {
  SplitEnglish splitter("");
  std::string input = "HELLO";
  std::string result = splitter.toLower(input);
  EXPECT_EQ(result, "hello");
}

TEST(SplitEnglishToLowerTests, HandlesStringWithMixedCaseLetters) {
  SplitEnglish splitter("");
  std::string input = "HeLlO";
  std::string result = splitter.toLower(input);
  EXPECT_EQ(result, "hello");
}

TEST(SplitEnglishToLowerTests, HandlesStringWithNonAlphabetCharacters) {
  SplitEnglish splitter("");
  std::string input = "Hello123!";
  std::string result = splitter.toLower(input);
  EXPECT_EQ(result, "hello123!");
}

TEST(SplitEnglishToLowerTests, HandlesStringWithSpaces) {
  SplitEnglish splitter("");
  std::string input = "Hello World";
  std::string result = splitter.toLower(input);
  EXPECT_EQ(result, "hello world");
}

#endif