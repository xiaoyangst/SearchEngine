/**
  ******************************************************************************
  * @file           : WebPageProducer.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024/12/10
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEPRODUCER_H_
#define SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEPRODUCER_H_
#include <memory>
#include "WebPage.h"
#include "WebPageOffset.h"
#include "WebPageRemove.h"
#include "WebPageInvert.h"
#include "utils/splitword/SplitChinese.h"
#include "utils/base/noncopyable.h"
class WebPageProducer : public noncopyable{
 public:
  explicit WebPageProducer(std::string path);
  void start();
  ~WebPageProducer() = default;
 private:
  std::string m_path;
  std::unique_ptr<WebPage> m_web_page;
  std::unique_ptr<WebPageOffset> m_web_page_offset;
  std::unique_ptr<WebPageRemove> m_web_page_remove;
  std::unique_ptr<WebPageInvert> m_web_page_invert;
  std::shared_ptr<SplitChinese> m_split_chinese;
};

#endif //SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEPRODUCER_H_
