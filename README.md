# fc-C++11 v0.0.1

[![Build Status](https://travis-ci.org/GrayFlow-Institute/fc-cpp.svg?branch=master)](https://travis-ci.org/GrayFlow-Institute/fc-cpp)

一个在 C++11 上使用高阶函数链式调用的库。

- [C++11 版本](https://github.com/GrayFlow-Institute/fc-cpp)
- [Python 版本](https://github.com/Riparo/fc-python)

## 用法

### 基于 Vector

一般的，我们使用 C++ STL 的 std::vector 来作为动态数组传递给 Fc 模板类，例如

```cpp
#include "Fc.h"
#include <vector>

using namespace std;

int main(){
  vector<int> l = {
      1, 2, 3, 4, 5, 6
  };

  auto v = Fc<int>(l).map([](int x) {
    return x + 1;
  }).filter([](int x) {
    return x > 3;
  }).reduce([](int x, int y) {
    return x + y;
  });

  assert(v==22);
}
```

### 基于迭代器

当然，Fc 也支持使用迭代器来**拷贝**容器到内建的 vector，以提高**灵活性**和**兼容**更多容器

```cpp
#include "Fc.h"
#include <list>

using namespace std;

int main(){
  list<int> l = {
      1, 2, 3, 4, 5, 6
  };

  auto v = Fc<int>(l.begin(),l.end()).map([](int x) {
    return x + 1;
  }).filter([](int x) {
    return x > 3;
  }).reduce([](int x, int y) {
    return x + y;
  });

  assert(v==22);
}
```

## 已完成

## 待扩展

- [ ] **可扩展地**支持更多的功能性函数
- [ ] 优化性能
- [ ] 增加灵活性
- [ ] 支持迭代器
- [ ] 构建安装包

## 更新历史

- 2018-06-23 v0.0.1 文档编写