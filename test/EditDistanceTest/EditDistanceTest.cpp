#include "src/online/server/EditDistance.h"

TEST(EditDistanceTest, editDiatance) {
  std::string key = "中国";

  std::string t1 = "中国";
  std::string t2 = "中国居民";
  std::string t3 = "中东国";
  std::string t4 = "中国社会主义";
  std::string t5 = "中国美女";
  std::string t6 = "江山社稷与中国大学";

  std::string t7 = "暂时中止";
  std::string t8 = "国家博物馆";

  std::string t9 = "中国民航";
  std::string t10 = "中国共产党";

  std::cout << EditDistance::editDistance(key, t1) << std::endl;// 0
  std::cout << EditDistance::editDistance(key, t2) << std::endl;// 2
  std::cout << EditDistance::editDistance(key, t3) << std::endl;// 1
  std::cout << EditDistance::editDistance(key, t4) << std::endl;// 4
  std::cout << EditDistance::editDistance(key, t5) << std::endl;// 2
  std::cout << EditDistance::editDistance(key, t6) << std::endl;// 7
  std::cout << EditDistance::editDistance(key, t7) << std::endl;// 3
  std::cout << EditDistance::editDistance(key, t8) << std::endl;// 5
  std::cout << EditDistance::editDistance(key, t9) << std::endl;// 2
  std::cout << EditDistance::editDistance(key, t10) << std::endl;// 3
  EXPECT_LT(EditDistance::editDistance(key, t1), EditDistance::editDistance(key, t2));
}