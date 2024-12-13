//
// Created by xy on 2024/12/13.
//
#include <iostream>
#include <memory>
#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <string>
#include <sstream>

#include "Singleton.h"

enum LOGLEVEL { EMERG, FATAL, ALERT, CRIT, ERROR, WARN, NOTICE, INFO, DEBUG };
#ifndef SEARCHENGINE_UTILS_BASE_LOG_H_
#define SEARCHENGINE_UTILS_BASE_LOG_H_
class Log : public Singleton<Log>, public std::enable_shared_from_this<Log> {
  friend class Singleton<Log>;
 public:
  void setLogLevel(log4cpp::Priority::Value priority){
    switch (priority) {
      case log4cpp::Priority::FATAL:
        m_rootCategory.setPriority(log4cpp::Priority::FATAL);
        break;
      case log4cpp::Priority::ERROR:
        m_rootCategory.setPriority(log4cpp::Priority::ERROR);
        break;
      case log4cpp::Priority::WARN:
        m_rootCategory.setPriority(log4cpp::Priority::WARN);
        break;
      case log4cpp::Priority::INFO:
        m_rootCategory.setPriority(log4cpp::Priority::INFO);
        break;
      case log4cpp::Priority::DEBUG:
        m_rootCategory.setPriority(log4cpp::Priority::DEBUG);
        break;
      default:
        m_rootCategory.setPriority(log4cpp::Priority::DEBUG);
        break;
    }
  }
  std::string int2string(int lineNumber){
    std::ostringstream oss;
    oss << lineNumber;
    return oss.str();
  }
  void fatal(const char *msg){
    m_rootCategory.fatal(msg);
  }
  void error(const char *msg){
    m_rootCategory.error(msg);
  }
  void warn(const char *msg){
    m_rootCategory.warn(msg);
  }
  void info(const char *msg){
    m_rootCategory.info(msg);
  }
  void debug(const char *msg){
    m_rootCategory.debug(msg);
  }
  ~Log(){
    log4cpp::Category::shutdown();
  }
 private:
  Log(): m_rootCategory(log4cpp::Category::getRoot().getInstance("rootCategory")){
    // 输出到控制台
    auto *osAppender = new log4cpp::OstreamAppender("console", &std::cout);
    auto *pLayoutA = new log4cpp::PatternLayout();
    pLayoutA->setConversionPattern("%d: %p %c %x: %m%n");
    osAppender->setLayout(pLayoutA);
    m_rootCategory.addAppender(osAppender);
    m_rootCategory.setPriority(log4cpp::Priority::DEBUG);

    // error
    auto *fileAppender = new log4cpp::FileAppender("fileAppender", "log/error.log");
    auto *pLayoutB = new log4cpp::PatternLayout();
    pLayoutB->setConversionPattern("%d: %p %c %x: %m%n");
    fileAppender->setLayout(pLayoutB);
    m_rootCategory.addAppender(fileAppender);
    m_rootCategory.setPriority(log4cpp::Priority::ERROR);

    // 日志回滚
    auto *rollingFileAppender = new log4cpp::RollingFileAppender(
        "rollingFileAppender", "log/roll.log", 5 * 1024, 5); // 5M（超过就新创建一个）,备份文件5个
    auto *pLayoutC = new log4cpp::PatternLayout();
    pLayoutC->setConversionPattern("%d: %p %c %x: %m%n");
    rollingFileAppender->setLayout(pLayoutC);
    m_rootCategory.addAppender(rollingFileAppender);
    m_rootCategory.setPriority(log4cpp::Priority::ERROR);
  }
 private:
  log4cpp::Category &m_rootCategory;
};

#define catMsg(msg) std::string(msg).append(" {fileName:")\
    .append(__FILE__).append(" functionName:")\
    .append(__func__).append(" lineNumber:")\
    .append(Log::Singleton::getInstance()->int2string(__LINE__)).append("}").c_str()

#define logSetLogLevel(priority) Log::Singleton::getInstance()->setLogLevel(priority)
#define ERROR_LOG(msg) Log::Singleton::getInstance()->error(catMsg(msg))
#define WARN_LOG(msg) Log::Singleton::getInstance()->warn(catMsg(msg))
#define INFO_LOG(msg) Log::Singleton::getInstance()->info(catMsg(msg))
#define DEBUG_LOG(msg) Log::Singleton::getInstance()->debug(catMsg(msg))
#define FATAL_LOG(msg) Log::Singleton::getInstance()->fatal(catMsg(msg))

#endif //SEARCHENGINE_UTILS_BASE_LOG_H_
