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

  void logMessage(log4cpp::Priority::PriorityLevel level, const char *format, va_list args) {
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    switch (level) {
      case log4cpp::Priority::FATAL:
        m_rootCategory.fatal(buffer);
        break;
      case log4cpp::Priority::ERROR:
        m_rootCategory.error(buffer);
        break;
      case log4cpp::Priority::WARN:
        m_rootCategory.warn(buffer);
        break;
      case log4cpp::Priority::INFO:
        m_rootCategory.info(buffer);
        break;
      case log4cpp::Priority::DEBUG:
        m_rootCategory.debug(buffer);
        break;
      default:
        m_rootCategory.info(buffer);
        break;
    }
  }

  std::string int2string(int lineNumber){
    std::ostringstream oss;
    oss << lineNumber;
    return oss.str();
  }
  void fatal(const char *format, ...) {
    va_list args;
    va_start(args, format);
    logMessage(log4cpp::Priority::FATAL, format, args);
    va_end(args);
  }

  void error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    logMessage(log4cpp::Priority::ERROR, format, args);
    va_end(args);
  }

  void warn(const char *format, ...) {
    va_list args;
    va_start(args, format);
    logMessage(log4cpp::Priority::WARN, format, args);
    va_end(args);
  }

  void info(const char *format, ...) {
    va_list args;
    va_start(args, format);
    logMessage(log4cpp::Priority::INFO, format, args);
    va_end(args);
  }

  void debug(const char *format, ...) {
    va_list args;
    va_start(args, format);
    logMessage(log4cpp::Priority::DEBUG, format, args);
    va_end(args);
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

    setLogLevel(log4cpp::Priority::INFO);
  }
 private:
  log4cpp::Category &m_rootCategory;
};



#define catMsg(fmt, ...) Log::Singleton::getInstance()->formatString(fmt " {file:%s func:%s line:%d}", __VA_ARGS__, __FILE__, __func__, __LINE__)
#define logSetLogLevel(priority) Log::Singleton::getInstance()->setLogLevel(priority)
#define ERROR_LOG(fmt, ...) Log::Singleton::getInstance()->error(fmt, ##__VA_ARGS__)
#define WARN_LOG(fmt, ...) Log::Singleton::getInstance()->warn(fmt, ##__VA_ARGS__)
#define INFO_LOG(fmt, ...) Log::Singleton::getInstance()->info(fmt, ##__VA_ARGS__)
#define DEBUG_LOG(fmt, ...) Log::Singleton::getInstance()->debug(fmt, ##__VA_ARGS__)
#define FATAL_LOG(fmt, ...) Log::Singleton::getInstance()->fatal(fmt, ##__VA_ARGS__)

#endif //SEARCHENGINE_UTILS_BASE_LOG_H_
