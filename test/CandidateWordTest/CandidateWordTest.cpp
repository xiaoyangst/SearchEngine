#include "online/server/CandidateWord.h"

TEST(CandidateWordTest, CandidateWords) {
  CandidateWord preheat("data/en_dict.dat", "data/en_invert.dat");
  EXPECT_TRUE(preheat.preheat());
}
