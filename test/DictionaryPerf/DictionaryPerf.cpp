#include <benchmark/benchmark.h>
#include "src/offline/keyword/Dictionary.h"
#include "utils/base/Configure.h"
#include "utils/base/Singleton.h"
#include "utils/splitword/SplitTool.h"
#include "utils/splitword/SplitEnglish.h"

static void bench_src_buildMap(benchmark::State &state) {
  std::string en_stop = Configure::getInstance()->get("en_stop").value();
  std::string en_corpus = Configure::getInstance()->get("en_corpus").value();
  std::string en_dict = Configure::getInstance()->get("en_dict").value();
  std::string en_invert = Configure::getInstance()->get("en_invert").value();
  std::shared_ptr<SplitTool> en_split_tool = std::make_shared<SplitEnglish>(en_stop);
  auto m_en_dictionary = std::make_unique<Dictionary>(en_corpus, en_dict, en_split_tool);

  for (auto _ : state) {
    m_en_dictionary->buildMap();
  }
}
static void bench_target_buildMap(benchmark::State &state) {
  std::string en_stop = Configure::getInstance()->get("en_stop").value();
  std::string en_corpus = Configure::getInstance()->get("en_corpus").value();
  std::string en_dict = Configure::getInstance()->get("en_dict").value();
  std::string en_invert = Configure::getInstance()->get("en_invert").value();
  std::shared_ptr<SplitTool> en_split_tool = std::make_shared<SplitEnglish>(en_stop);
  auto m_en_dictionary = std::make_unique<Dictionary>(en_corpus, en_dict, en_split_tool);

  for (auto _ : state) {
    m_en_dictionary->buildMap_();
  }
}

// 注册基准测试
BENCHMARK(bench_target_buildMap);
BENCHMARK(bench_src_buildMap);

BENCHMARK_MAIN();