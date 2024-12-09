# 库

网络库：libhv

Json库：json.hpp

测试框架：gtest

分词库：cppjieba

# 面试准备

## libhv网络库

### 为什么选择用 libhv 网络库

### 讲讲 Reactor 模型

## 用到哪些设计模式？

* 单例模式
* 策略模式

### 哪里用到单例模式？为什么要用到单例模式？

提供推荐词和网页推荐的在线服务器用到单例模式。

因为服务器的实力一个程序只能有一个，不能有多个，就选择用单例模式。

### 手写一个线程安全的单例模式

#### 2024/12/5

```c++
#include <mutex>
#include <memory>
using namespace std;
class Singleton {
public:
	static shared_ptr<Singleton> getInstance() {
		static once_flag flag;
		call_once(flag, [&]() {
			m_instance = make_shared<Singleton>();
			});
		return m_instance;
	}
private:
	static shared_ptr<Singleton> m_instance;
};
shared_ptr<Singleton> Singleton::m_instance = nullptr;
```

反省：实现过程中遇到哪些问题？

忘记对 static 成员进行初始化，还有初始化的时候不要加 static 关键字。

静态成员规则：

1. private的静态数据成员无法在类之外直接访问（显然）
2. **对于静态数据成员的初始化，必须放在类外**（一般紧接着类的定义，这是规则 1 的特殊情况）
3. <font color="red">静态数据成员初始化时不能在数据类型前面加 static</font>，在数据成员名前面要加上类名+作用域限定符
4. 如果有多条静态数据成员，那么它们的初始化顺序需要与声明顺序一致（规范）
5. 静态成员在访问时可以通过对象访问，**也可以直接通过类名::成员名的形式**（更常用）

### 哪里用到策略模式？为什么要用到策略模式？

在拿到原始文件的时候，需要对文件中的语句进行分词，这有利于构建字典和索引已经后面的倒排索引。而不同语言的文本分词规则不同，考虑到项目的可扩展性，创建一个分词工具的抽象类，所有不同语言的分词工具都继承这个类进行特定接口的实现和自身特性的功能实现。那么，后续如果涉及到其它语言，只要继承该抽象类进行实现即可，在其他地方的逻辑不用更改，只需要传递这个类的实例对象即可。

### 设计模式六大基本原则（复习）

单一职责原则：一个类完成自己特定的功能，而不该包含其它类应该实现的功能

开闭原则：对于扩展是开放的，修改是关闭的

接口分离原则：使用多个小的专门的接口，而不是一个总的大接口

里氏代换原则：派生类可以扩展基类的功能，但不可以改变基类的原有功能

依赖倒转原则：依赖于抽象接口，不依赖于具体的实现

迪米特法原则：一个类应该对其它类尽可能保持少的了解

## 讲讲这个项目

<font color="red">务必提及已掌握知识点关键词，引导面试官的提问!!!</font>

## 谈谈遇到哪些问题？如何解决的？

### 性能优化：离线模式生成文件，觉得有点慢

用 perf 工具生成火焰图，明显看到有个地方的函数调用的高度很高且表明平稳，确定这个地方的性能损耗很大。

然后知晓这块调用大量的 正则表达式的处理函数，从网上简单查询 C++ 的正则表达式接口确实会带来性能下降问题，这边就针对这块进行优化。将这块地方的处理换成用字符串的方式去写规则来符合之前的要求，性能上明显提升，很快就生成字典，索引和倒排索引文件。

因此，在设计正则表达式的时候要测试性能问题，已经写出合理的规则，避免无效的回溯。

### 为什么正则表达式接口确实会带来性能下降问题？

目前实现正则表达式引擎的方式有两种：

DFA 从匹配文本入手，从左到右，每个字符不会匹配两次，它的时间复杂度是多项式的，所以通常情况下，它的速度更快，但支持的特性很少，不支持捕获组、各种引用等等；

而 NFA 则是从正则表达式入手，不断读入字符，尝试是否匹配当前正则，不匹配则吐出字符重新尝试，通常它的速度比较慢，最优时间复杂度为多项式的，最差情况为指数级的。

但NFA支持更多的特性，因而绝大多数编程场景下面对的是NFA。

### 正则表达式的基本语法



### 网页去重：simhash算法



## 讲讲智能指针的使用

### 为什么要用智能指针？

类的析构函数负责类对象资源的回收，如果涉及到堆内存，必须要在析构函数中合理回收，否则就会出现内存泄露问题。而

类对象本身如果是局部对象会自动 delete 并且调用析构函数，但如果是堆内存申请的对象，还需要在合适的时机进行 delete，否则会出现内存泄漏。如果因为出现异常，还会导致没有执行到 delete 操作而导致内存泄漏问题。

智能指针可以解决这两个问题。由于智能指针是采用 RAII 思想设计，因此是异常安全的，可以保证即便出现异常，管理的对象也能正常析构。还有合适的时机进行 delete 的问题也由 智能指针揽下，只要正确使用智能指针，前面提出的问题就不用再考虑了。

### 有哪些智能指针？详细展开讲讲

C++11 有三种智能指针，shared_ptr，unique_ptr，weak_ptr。

#### shared_ptr

shared_ptr 可以有多个实例并且指向同一个对象，等到要 delete 管理的对象的时候，如果判断引用计数为 1 就正常 delete，否则只是让引用计数 -1。一个 shared_ptr 实例指向管理的对象，同时还指向一个控制块，控制块中最关键的部分就是引用计数，只有正确的让引用计数增加，才能让对象的管理不会出错，否则会导致多次 delete 和 多次析构的问题，导致程序崩溃。shared_ptr 在使用的过程中，要特别注意两个点。一个点是不要让 shared_ptr 去接管一个已经被 shared_ptr 管理的对象的原始指针，因为当 shared_ptr 接受的是原始指针就会为其创建一个控制块，这导致引用计数没有合理增加，因为它们没有共享同一个控制块中的引用计数，引用计数没有正确增加，就是错误使用 shared_ptr 的标志，会导致多次 delete 和 多次析构的问题。还有一点是，如果这个对象本身已经是被 shared_ptr 管理，我们要获取某个对象的 this 指针的时候，我们如果想要这个对象的画，让返回 this 指针的这个类 继承一个模板类 enable_shared_from_this ，然后调用 shared_from_this即可，它会创建指向当前对象的 std::shared_ptr 却不创建多余控制块。 

在创建 shared_ptr 对象的时候，通常选择 make_shared 方法创建，它在性能上要比 new 的方式来创建要高，因为指向对象和控制块的生成会一起完成，而不是分两次操作，这也保证 shared_ptr 对象能够被正确的构建完成。

#### weak_ptr



#### unique_ptr



### 聊聊RAII以及优缺点

### 手写 shared_ptr

### 手写 weak_ptr

### 手写 unique_ptr

## 为什么要构建倒排索引？说说原理和好处

## Redis

## 手写代码

### 快速排序

### 堆排序

### 线程池

### 阻塞队列

### 无锁队列

### 读写锁

### 多线程打印数据(间隔输出，有序输出等等)

本质上是考察线程间的同步问题，这里选择第一道题作为我们的题目。

<font color="red">三个线程分别打印 A，B，C，要求这三个线程一起运行，打印 n 次，输出形如“ABCABCABC....”的字符串。</font>

```c++
std::mutex mtx_;
std::condition_variable cv_;
int flag = 0;
void funA(int n) {
  for (int i = 0; i < n; ++i) {
    std::unique_lock<std::mutex> lck(mtx_);
    cv_.wait(lck, []() { return flag == 0; });
    flag = 1;
    cv_.notify_one();
    std::cout << "A";
  }
}
void funB(int n) {
  for (int i = 0; i < n; ++i) {
    std::unique_lock<std::mutex> lck(mtx_);
    cv_.wait(lck, []() { return flag == 1; });
    flag = 2;
    cv_.notify_one();
    std::cout << "B";
  }
}
void funC(int n) {
  for (int i = 0; i < n; ++i) {
    std::unique_lock<std::mutex> lck(mtx_);
    cv_.wait(lck, []() { return flag == 2; });
    flag = 0;
    cv_.notify_one();
    std::cout << "C";
  }
}
```

用互斥锁和条件变量达到线程同步的效果，同时还添加一个 flag 变量（非常关键）。

利用 flag 的值情况来保证哪些线程当前应该阻塞，那些线程当前应该接触阻塞。

&nbsp;

<font color="red">两个线程交替打印 0~100 的奇偶数</font>

```c++
std::mutex mtx_;
std::condition_variable cv_;
int flag = 0;
void funA() {
  for (int i = 0; i < 100; ++i) {
    std::unique_lock<std::mutex> lck(mtx_);
    cv_.wait(lck, []() { return flag % 2 == 0; });
    cout << flag++ << " ";
    if (flag > 100) {
      cv_.notify_one();
      return;
    }
    cv_.notify_one();
  }
}
void funB() {
  for (int i = 0; i < 100; ++i) {
    std::unique_lock<std::mutex> lck(mtx_);
    cv_.wait(lck, []() { return flag % 2 != 0; });
    if ((flag + 1) > 100) {
      cv_.notify_one();
      return;
    }
    cout << flag++ << " ";
    cv_.notify_one();
  }
}
```

&nbsp;

<font color="red">通过 N 个线程顺序循环打印从 0 至 100</font>（非常有难度）

这道题乍一看确实蛮有难度的，我们不可以像第一道题那样，修改参数的值来唤醒特定的线程，这里的线程数量是不确定。但是，每个线程有自己的 ID（不知道通过  get_id 方法那种获取，而是我们自己赋予），可利用这点来解决这个问题。

```c++
#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
using namespace std;

std::mutex mtx_;
std::condition_variable cv_;
int flag = 0;
void fun(int id, int thread_num, int target) {
  while (true) {
    unique_lock<std::mutex> uq(mtx_);
    cv_.wait(uq, [&]() {
      return flag % thread_num == id || flag > target;
    });
    if (flag > target) {	// 集体唤醒，大家退出线程
      cv_.notify_all();
      return;
    }
    cout << flag << " ";
    flag++;
    cv_.notify_all();
  }
}

int main() {

  int Thread_num = 0;

  cout << "input thread nums: ";
  cin >> Thread_num;

  std::vector<thread> threads;

  for (int i = 0; i < Thread_num; ++i) {
    threads.emplace_back(fun, i, Thread_num, 100);
  }

  for (auto &thread : threads) {
    thread.join();
  }
  return 0;
}
```

**为什么不能用 this_thread::get_id() 来获取线程 id 参与计算？**

因为这个类型并不是一个简单的整数类型，而是一个用于标识线程的抽象类型。虽然它可以用于比较线程是否相同，但它本身并没有直接暴露可以进行数值计算的底层数据。

因此，我们在创建特定数量线程的时候，就以 for 循环中的 i 来标识线程 id。

&nbsp;

**输出结果之后，错写为 notify_one() ？**

因为我们是多个线程在等待，但是又不确定会是哪个线程来执行下一个任务，因此如果你是 notify_one() 极大概率无法唤醒到本该执行的县城，导致死锁。但如果是 notify_all() 就一定可以保证本该执行的线程被唤醒且往下执行。

&nbsp;

**忘记写 flag > target ？**

由于在下面我们会判断 flag > target，从而让我们的循环退出。因此，后面在进行退出时发出的集体唤醒，如果没有这个条件判断的话，会导致死锁，即无法脱离出阻塞，我指得是这个判断：` flag % thread_num == id || flag > target`。

### 手写String

### 手写Vector

## 八股文

### 引用占用空间吗？

占用，且和指针的大小一致。

我们讲引用就是受限的指针，这让它在使用上更加安全，这也是推荐尽可能用引用的原因。

### 指针和引用的区别是什么？

指针可以指向 nullptr，但引用必须绑定一个对象。

指针可以进行加减运算，但引用不可以。

指针可以改变指向的对象，但引用只能一直指向最开始指向的对象。

指针指向的是一个对象的地址，引用是绑定对象的别名，因此和对象共享地址。也就是说指针需要 * 解引用才能访问到变量的值，而运用可以直接访问。

### 悬挂指针和野指针

### 避免野指针

### 结构体可以直接赋值吗？

https://blog.csdn.net/Ivan804638781/article/details/110913901

### final 和 override 关键字

### volatile 关键字

### 全局变量和局部变量有什么区别？操作系统和编译器是怎么知道的？

### 动态多态发生的基础条件

### 如何限制类的对象只能在堆上创建？如何限制对象只能在栈上创建？

### C++ 编译器会给一个空类自动生成哪些函数？

### OSI七层模型

### TCP建立连接为什么要三次握手

## 算法题

### 删除链表的第k个结点

### 二叉树非递归中序遍历

