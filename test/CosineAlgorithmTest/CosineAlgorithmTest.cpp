#include <gtest/gtest.h>
#include <cmath>
#include "online/server/CosineAlgorithm.h"
// 测试两个完全相同的PageWeight的余弦相似度应为1
TEST(CosineAlgorithmTest, Similarity_PerfectMatch) {
  PageWeight lhs = {{"1", 0.5}, {"2", 0.3}};
  PageWeight rhs = {{"1", 0.5}, {"2", 0.3}};
  double similarity = CosineAlgorithm::CosineSimilarity(lhs, rhs);
  EXPECT_DOUBLE_EQ(1.0, similarity);
}

// 测试两个完全不相关的PageWeight的余弦相似度应为0
TEST(CosineAlgorithmTest, Similarity_CompletelyUnrelated) { //
  PageWeight lhs = {{"1", 0.5}, {"2", 0.3}};
  PageWeight rhs = {{"9", 0.7}, {"6", 0.8}};
  double similarity = CosineAlgorithm::CosineSimilarity(lhs, rhs);
  EXPECT_DOUBLE_EQ(0.0, similarity);
}

// 测试包含公共元素但其权重不同的PageWeight的余弦相似度应不为0也不为1
TEST(CosineAlgorithmTest, Similarity_NotZeroOrOne) {
  // 创建两个 PageWeight 对象，公共元素的权重不同
  PageWeight lhs = {{"1", 0.5}, {"2", 0.3}};
  PageWeight rhs = {{"1", 0.2}, {"2", 0.8}};

  // 计算余弦相似度
  double similarity = CosineAlgorithm::CosineSimilarity(lhs, rhs);

  // 验证余弦相似度不为 0
  EXPECT_NE(similarity, 0.0);

  // 验证余弦相似度不为 1
  EXPECT_NE(similarity, 1.0);

  // 还可以验证结果是否落在合理范围内 (例如 0 到 1 之间)
  EXPECT_GE(similarity, 0.0);
  EXPECT_LE(similarity, 1.0);
}



// 测试空PageWeight的余弦相似度，对于任何非空的PageWeight应为0
TEST(CosineAlgorithmTest, Similarity_EmptyLHS) {
  PageWeight lhs = {};
  PageWeight rhs = {{"1", 0.5}, {"2", 0.3}};
  double similarity = CosineAlgorithm::CosineSimilarity(lhs, rhs);
  EXPECT_DOUBLE_EQ(0.0, similarity);
}

// 测试空PageWeight的余弦相似度，对于任何非空的PageWeight应为0
TEST(CosineAlgorithmTest, Similarity_EmptyRHS) {
  PageWeight lhs = {{"1", 0.5}, {"2", 0.3}};
  PageWeight rhs = {};
  double similarity = CosineAlgorithm::CosineSimilarity(lhs, rhs);
  EXPECT_DOUBLE_EQ(0.0, similarity);
}

// 测试两个空PageWeight的余弦相似度，应为0
TEST(CosineAlgorithmTest, Similarity_EmptyBoth) {
  PageWeight lhs = {};
  PageWeight rhs = {};
  double similarity = CosineAlgorithm::CosineSimilarity(lhs, rhs);
  EXPECT_DOUBLE_EQ(0.0, similarity);
}