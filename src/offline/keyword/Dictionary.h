/**
  ******************************************************************************
  * @file           : Dictionary.h
  * @author         : xy
  * @brief          : 生成词典文件的基类
  * @attention      : None
  * @date           : 2024/11/26
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_KEYWORD_DICTIONARY_H_
#define SEARCHENGINE_SRC_OFFLINE_KEYWORD_DICTIONARY_H_
#include <string>
#include <unordered_map>
#include <memory>
#include "utils/splitword/SplitTool.h"
class Dictionary {
 public:
    explicit Dictionary(std::string corpus_dir,std::string dict_path,std::shared_ptr<SplitTool> split_tool);
    virtual ~Dictionary() = default;
    virtual bool buildMap();  // 构建词典
    virtual bool CreateDictionary();  // 生成词典文件
 protected:
  std::string m_corpus_dir;
  std::string m_dict_path;
  std::shared_ptr<SplitTool> m_split_tool;  // 分词工具
  std::unordered_map<std::string,unsigned int> m_map;
};

#endif //SEARCHENGINE_SRC_OFFLINE_KEYWORD_DICTIONARY_H_
