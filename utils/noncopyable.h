/**
  ******************************************************************************
  * @file           : noncopyable.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024/11/22
  ******************************************************************************
  */

#ifndef STUDY__NONCOPYABLE_H_
#define STUDY__NONCOPYABLE_H_

class noncopyable {
 protected:
  noncopyable() = default;
  ~noncopyable() = default;
  // 删除拷贝构造和拷贝赋值
  noncopyable(const noncopyable &) = delete;
  noncopyable &operator=(const noncopyable &) = delete;
  // 删除移动构造和移动赋值
  noncopyable(noncopyable &&) = delete;
  noncopyable &operator=(noncopyable &&) = delete;
};


#endif //STUDY__NONCOPYABLE_H_
