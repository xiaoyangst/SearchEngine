/**
  ******************************************************************************
  * @file           : Singleton.h
  * @author         : xy
  * @brief          : 线程安全模板单例类
  * @attention      : 使用者 必须让可执行程序 链接 pthread，否则 报错 std::system_error（call_once 触发）
  * @date           : 2024/11/26
  ******************************************************************************
  */

#ifndef SEARCHENGINE_UTILS_SINGLETON_H_
#define SEARCHENGINE_UTILS_SINGLETON_H_

#include <memory>
#include <mutex>
template<typename T>
class Singleton{
 public:
  static T* getInstance(){
    static std::once_flag m_flag;
    std::call_once(m_flag,[&](){
      m_instance = new T();
      atexit(&destroy);
    });
    return m_instance;
  }

  // 删除拷贝构造和拷贝赋值
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  // 删除移动构造和移动赋值构造
  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;
 protected:
  Singleton() = default;
  ~Singleton() = default;
  static void destroy(){
    if (m_instance){
      delete m_instance;
      m_instance = nullptr;
    }
  }
 private:
  static T* m_instance;
};
template<typename T>
T* Singleton<T>::m_instance = nullptr;


#endif //SEARCHENGINE_UTILS_SINGLETON_H_
