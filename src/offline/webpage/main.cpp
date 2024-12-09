#include "WebPage.h"
#include "WebPageOffset.h"
#include "WebPageRemove.h"
#include "SimHashWebPage.h"
#include "WebPageInvert.h"
#include "utils/splitword/SplitChinese.h"
int main(){
#if 1
  std::cout << "Web Page" << std::endl;
  WebPage page("sources/project/page", "data/webpage.dat");
  page.Parse();
  page.Generate();

  std::cout << "Web Page Offset" << std::endl;
  WebPageOffset offset_page("data/webpage.dat", "data/webpage_offset.dat");
  offset_page.Parse();
  offset_page.Generate();

  std::cout << "Web Page Remove" << std::endl;
  WebPageRemove remove_page("data/webpage.dat", "data/webpage_offset.dat"
                            ,"data/new_webpage.dat", "data/new_webpage_index.dat", "conf/simhash.json");
  remove_page.buildNewDict();
  remove_page.buildNewIndex();

  std::cout << "Web Page Invert" << std::endl;
  auto spl = std::make_shared<SplitChinese>("sources/project/dict/stop_words.utf8", "conf/jieba.json");
  WebPageInvert web_page_invert("data/webpage_invert.dat", "data/new_webpage.dat",
                                "data/new_webpage_index.dat",spl);
  web_page_invert.buildMap();
  web_page_invert.createInvert();
  return 0;
#endif
  SimHashWebPage sim_hash_web_page("sources/project/dict/jieba.dict.utf8",
                                    "sources/project/dict/hmm_model.utf8",
                                    "sources/project/dict/idf.utf8",
                                    "sources/project/dict/stop_words.utf8");

    auto r1 = sim_hash_web_page.getSimHash("我是中国人");
    auto r2 = sim_hash_web_page.getSimHash("我是中国人");
    std::cout<<"r1: "<<r1<<std::endl;
    std::cout<<"r2: "<<r2<<std::endl;
    std::cout<<"isEqual: "<<sim_hash_web_page.isEqual(r1,r2)<<std::endl;

  auto r3 = sim_hash_web_page.getSimHash("我是中国人");
  auto r4 = sim_hash_web_page.getSimHash("我是李白");
  std::cout<<"r3: "<<r3<<std::endl;
  std::cout<<"r4: "<<r4<<std::endl;
  std::cout<<"isEqual: "<<sim_hash_web_page.isEqual(r3,r4)<<std::endl;
    return 0;
}