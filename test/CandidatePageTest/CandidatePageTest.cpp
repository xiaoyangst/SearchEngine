#include "online/server/CandidatePage.h"
#include "utils/base/SingleWord.h"
#include <thread>
#include <chrono>
TEST(CandidatePageTest, CandidatePages) {
  CandidatePage candidate_page("data/webpage_invert.dat", "data/new_webpage_offset.dat");
  EXPECT_TRUE(candidate_page.preheat());
  std::string data = "我爱北京天安门";
  CandMap result;
  candidate_page.CandidatePages(SingleWord::splitString(data),result);
  for (const auto& item:result) {
    std::cout<<"doc_id = "<<item.first<< std::endl;
    for (const auto& pa:item.second) {
      std::cout<<pa.first<<" "<<pa.second<<std::endl;
    }
    std::cout<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}