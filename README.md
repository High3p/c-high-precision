

# HP - 高精度运算库 (High Precision)

一个基于 C++ 的高精度整数与小数运算库，支持任意长度的整数和小数四则运算、快速幂、精度控制。

## 简介

HP (High Precision) 是一个专为高精度计算设计的 C++ 头文件库。该库不依赖任何外部库，仅通过简单的头文件引入即可使用，能够处理任意长度的整数和小数运算，解决了传统数据类型（如 `int`、`long`、`double`）在处理大数时的溢出和精度丢失问题。

### 主要特性

- **任意精度整数** - 支持任意长度整数的加减乘除运算，包括负数处理
- **任意精度小数** - 支持任意长度小数的四则运算，可自定义精度
- **快速幂运算** - 支持整数、小数、双精度浮点数的快速幂计算
- **安全类型转换** - 提供从高精度整数到 `long long` 的安全转换，带溢出检测
- **轻量级** - 单头文件设计，无外部依赖，零运行时开销
- **易用性** - 提供工厂函数 `create_hp()` 和 `create_hp_dec()` 快速创建对象

## 目录结构

```
high-precision/
├── HPannex.h      # 辅助函数和类型转换
├── HPdec.h        # 高精度小数实现
├── HPint.h        # 高精度整数实现  
├── HPmath.h       # 数学运算（快速幂等）
├── Introduction.txt  # 项目介绍
├── LICENSE        # 开源许可证
└── README.md      # 说明文档
```

## 安装

### 方式一：直接包含头文件

将项目中的 `.h` 文件复制到你的项目中，并在源文件开头添加：

```cpp
#include "HPannex.h"
using namespace std;
```

### 方式二：系统级安装

将所有 `.h` 文件复制到你的 include 目录（如 `/usr/include/` 或 `C:\Program Files\...\`），然后直接引用：

```cpp
#include <HPannex.h>
```

### 编译要求

- C++11 或更高版本的编译器
- 无外部依赖库

## 快速开始

### 高精度整数运算

```cpp
#include "HPannex.h"
using namespace std;

int main() {
    // 创建高精度整数
    HP_int a = create_hp("123456789012345678901234567890");
    HP_int b = create_hp("98765432109876543210");
    
    // 基本算术运算
    cout << a + b << endl;   // 高精度加法
    cout << a - b << endl;   // 高精度减法  
    cout << a * b << endl;   // 高精度乘法
    cout << a / b << endl;   // 高精度除法
    
    // 快速幂运算
    cout << HPpow(create_hp("2"), create_hp("100")) << endl;  // 2^100
    
    // 安全类型转换（带溢出检测）
    long long result = HI_TO_LL(a);
    if (result != LLONG_MIN) {
        cout << "转换成功: " << result << endl;
    }
    
    return 0;
}
```

### 高精度小数运算

```cpp
#include "HPannex.h"
using namespace std;

int main() {
    // 创建高精度小数
    HP_dec d1 = create_hp_dec("5.08320474913");
    HP_dec d2 = create_hp_dec("2.562391563502");
    
    // 设置精度（控制小数位数）
    precision = create_hp("5");  // 保留5位小数
    
    // 基本算术运算
    cout << d1 + d2 << endl;   // 加法
    cout << d1 - d2 << endl;   // 减法
    cout << d1 * d2 << endl;   // 乘法
    cout << d1 / d2 << endl;   // 除法
    
    return 0;
}
```

## API 参考

### HP_int - 高精度整数类型

| 函数/运算符 | 说明 |
|------------|------|
| `create_hp(str)` | 通过字符串创建高精度整数 |
| `HP_int + HP_int` | 加法运算 |
| `HP_int - HP_int` | 减法运算 |
| `HP_int * HP_int` | 乘法运算 |
| `HP_int / HP_int` | 除法运算 |
| `HI_TO_LL(HP_int)` | 转换为 `long long`（带溢出检测，失败返回 `LLONG_MIN`） |

### HP_dec - 高精度小数类型

| 函数/变量 | 说明 |
|----------|------|
| `create_hp_dec(str)` | 通过字符串创建高精度小数 |
| `precision` | 全局变量，控制小数运算精度（需设为 `HP_int` 类型） |
| `HP_dec + HP_dec` | 加法运算 |
| `HP_dec - HP_dec` | 减法运算 |
| `HP_dec * HP_dec` | 乘法运算 |
| `HP_dec / HP_dec` | 除法运算 |

### HPI_to_HPD / HPD_to_HPI - 类型转换

```cpp
// 高精度整数转高精度小数
HP_dec HPI_to_HPD(const HP_int& to);

// 高精度小数转高精度整数（自动取整）
HP_int HPD_to_HPI(const HP_dec& to);
```

### HPpow - 快速幂运算

```cpp
// 整数快速幂
HP_int HPpow(HP_int base, HP_int exponent);

// 小数快速幂  
HP_dec HPpow(HP_dec base, HP_int exponent);

// 双精度浮点数快速幂
double HPpow(double base, HP_int exponent);
```

## 应用场景

- **密码学** - 处理大素数、RSA 加密等需要大数运算的场景
- **科学计算** - 物理常数、天文数字、量子计算等领域
- **金融计算** - 精确货币计算，避免浮点误差
- **算法竞赛** - 处理超过 64 位范围的整数运算
- **数据分析** - 统计大样本数据时避免溢出

## 许可证

本项目采用 MIT 许可证开源，详情请参阅 LICENSE 文件。

## 贡献

欢迎提交 Issue 和 Pull Request 共同完善本项目。

## 联系方式

- 项目地址：https://gitee.com/High_P/high-precision