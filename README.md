# High-Precision

## 简介

High-Precision 是一个高精度数学计算 C++ 头文件库，提供整数、浮点数、 decimal 数及数学函数的高精度实现。

## 主要特性

- **HPint.h** - 高精度整数运算
- **HPdec.h** - 高精度浮点数/decimal 运算  
- **HPannex.h** - 附加功能扩展
- **HPmath.h** - 高精度数学函数库

## 使用方法

### 包含头文件

```cpp
#include "HPint.h"
#include "HPdec.h"
#include "HPannex.h"
#include "HPmath.h"
```

### 编译示例

```bash
g++ -o example example.cpp -std=c++11
```

## 项目结构

```
├── HPint.h      # 高精度整数
├── HPdec.h      # 高精度浮点数
├── HPannex.h    # 附加功能
├── HPmath.h     # 数学函数
├── LICENSE      # MIT 许可证
└── README.md    # 说明文档
```

## 更新日志

详细更新记录请查看 `update.md`。

## 许可证

MIT License - 查看 LICENSE 文件了解详情。