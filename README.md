# Toolib
我自己使用的一些工具库。

 [English](README_en.md)

## 写在前面
本项目的编码、检查和调用全部在 VS 中完成。它使用了在 C++23 中添加的模块，因此请检查您的设置。

**我不能保证它是安全的。**

### 模块

### bitIO
`bitarry` 是一个可以按位改变数据的类。

#### init
`bitarry()` -> 创建一个没有任何数据的空对象。

`bitarry(const size_t size)` -> 创建一个有 \<size\> 位（8 位对齐）的数组。

`bitarry(const unsigned char* arry, const size_t len)` -> 从一个无符号 char 数组创建一个数组，\<len\>是 char 数组中的字符数。

#### 函数
`bool setSize(const size_t bitsize)` -> 设置数组的大小。(只有当对象为空时才有效）

`bitarry read(const size_t v, const int len)` -> 读取 \<len\> 位并从 \<v\> 位开始。

`bool write(const size_t v, const int len, wood::bitarry bdata)` -> 从 \<v\> 位开始写入 \<len\> 位。(数据数组从 0 位开始)**警告：这个函数不检查数据数组是否有足够的位。**

`void Print(unsigned short CHD)` -> 打印数组数据到 stdout。Modoul 0: Char, Modoul 1: Hex, Modoul 2: Decimal number.

`const unsigned char* c_str()const` -> 返回数据指针。

`const size_t resize()const` -> 返回数组的大小。

`void setMermey(const unsigned char data)` -> 根据数据设置数组。

`bool good()const` -> 检查是否发生错误。

`const char* err()`> 获取错误信息。并重置错误标志。

#### 新增
`setMemModel(int model)` -> 设置读取的内存模型，0为正常的大端序模型（默认），1为局部小端序模型（单个unsigned char）内部。

例如：0x64(0110 0100)在模式0下被认为从低到高比特位依次是0010 0110，而模式1会认为它是0110 0100。但是不影响整体的储存，比如char str={'a','b'}在两种模式下均为str\[0\]='a',str\[1\]='b'。

### EDcode
一些编码的函数。现在只有 `ToBase64`的几种实现和`FromBase64`的实现。

注意：除了参数为`const char* str,unsigned char* buffer, int MaxLen`的实现，其他实现不会补充末尾的"="。