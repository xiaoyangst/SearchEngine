## SplitTool

分词工具抽象基类

```c++
SplitTool();
virtual ~SplitTool();
virtual vector<string> split(const string& sentence) = 0;
```

## SplitChinese

中文分词

```c++
vector<string> split(const string& sentence);
```

## SplitEnglish

英文分词

```c++
vector<string> split(const string& sentence);
```

## Dictionary

创建词典文件

先读取**语料**，进行**分词**处理，**构建**词典文件

```c++
void build(const string& path);
```

## DictionaryIndex

创建词典索引文件

先读取词典文件，构建词典索引文件

```c++
void build(const string& path);
```

## DictionaryProducer

创建词典文件+创建词典索引文件（构造函数中完成），提供查询接口

唯一提供给外界用的类

```c++
DictionaryProducer();
vector<string> query(const string& word);
```

