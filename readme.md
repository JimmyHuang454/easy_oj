# 本地 OJ

由于最近要机试，OJ 系统是自搭建的，资源较少，改题慢，用例错误时会减少分值（一次过才能拿满分），所以，提交前尽可能保证绝对正确！自己一个个输入用例，然后测试，这不是我风格！能自动化就自动化，能懒就懒。

## 用法

很简单，随便新建一个文件夹，里面仅包含一个.cpp 为后缀的源文件，和一个.txt 为后缀的用例。

## 例子

```cpp
#include <iostream>

using namespace std;

string str;

int main(void) {
  cin >> str;
  auto res = str.find("Hello World");
  if (res == string::npos) {
    cout << "NO" << endl;
  } else {
    cout << res << endl;
  }
}
```

```txt
[
abcdef
]
{
NO
}
==
[
Hello World.
]
{
0
}
```

打开一个终端，运行脚本。即可自动编译，然后测试：

