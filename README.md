# HP - 高精度运算库 (High Precision)

[![Version](https://img.shields.io/badge/version-1.5.3-blue)]()
[![License](https://img.shields.io/badge/license-MIT-green)]()
[![C++](https://img.shields.io/badge/C++-11%2B-orange)]()

🌍 **English** | [🇨🇳 中文](README_zh.md)

一个纯 C++ 头文件实现的高精度整数与小数运算库：支持任意长度的四则运算、快速幂与精度控制，**无任何外部依赖**。

---

## 简介

HP (High Precision) 是一个专为高精度计算设计的 C++ 头文件库。只需 `#include "HPannex.h"` 即可使用，解决传统数据类型（`int`、`long long`、`double`）处理大数时的**溢出**和**精度丢失**问题。

本项目从 0 开始手写，持续维护中！⭐

## 主要特性

- **任意精度整数（HP_int）**：加减乘除、负数处理
- **任意精度小数（HP_dec）**：四则运算、自定义精度控制
- **快速幂（HPpow）**：高精度快速幂运算
- **类型转换**：HP_int ↔ HP_dec，以及到 `long long` 的安全转换
- **轻量级**：纯头文件、零外部依赖、零运行时开销
- **易用性**：工厂函数 `create_hp()` / `create_hp_dec()`，且支持 `HP_int a = 10` 直接赋值
- **一键更新器**：内置 `update.bat` / `update.sh`，自动获取最新版本（支持地理位置自动选源：中国→Gitee，国外→GitHub）

## 目录结构

```
high-precision/
├── HPannex.h      # 总入口（伞式头文件，自动包含其他头文件）
├── HPint.h        # 高精度整数实现
├── HPdec.h        # 高精度小数实现
├── HPmath.h       # 数学运算（快速幂等）
├── update.bat     # Windows 一键更新器
├── update.sh      # Linux/macOS 一键更新器
├── update.md      # 更新日志
├── LICENSE        # MIT 开源许可证
└── README.md      # 说明文档
```

## 安装

### 方式一：直接包含头文件
将 `.h` 文件复制到项目目录，源文件开头写：
```cpp
#include "HPannex.h"
using namespace std;
```

### 方式二：系统级安装
把所有 `.h` 文件放入编译器 include 目录（如 `/usr/include/` 或 Dev-C++ 的 include 目录），然后：
```cpp
#include <HPannex.h>
```

### 方式三：一键获取最新版
- Windows：双击运行 `update.bat`
- Linux/macOS：终端执行 `bash update.sh`

### 编译要求
- C++11 或更高版本
- 无外部依赖

## 快速开始

### 高精度整数
```cpp
#include "HPannex.h"
using namespace std;

int main() {
    HP_int a = create_hp("123456789012345678901234567890");
    HP_int b = create_hp("98765432109876543210");

    cout << a + b << endl;   // 加法
    cout << a - b << endl;   // 减法
    cout << a * b << endl;   // 乘法
    cout << a / b << endl;   // 除法

    // 快速幂：2^100
    cout << HPpow(create_hp("2"), create_hp("100")) << endl;

    // 1.5 版本起，可以直接用 int/long long 赋值
    HP_int c = 10;
    c += 5;
    cout << c << endl;       // 输出 15
    return 0;
}
```

### 高精度小数
```cpp
#include "HPannex.h"
using namespace std;

int main() {
    HP_dec d1 = create_hp_dec("5.08320474913");
    HP_dec d2 = create_hp_dec("2.562391563502");

    cout << d1 + d2 << endl;   // 加法
    cout << d1 - d2 << endl;   // 减法
    cout << d1 * d2 << endl;   // 乘法
    cout << d1 / d2 << endl;   // 除法
    return 0;
}
```

## API 参考

### HP_int - 高精度整数
| 函数/运算符 | 说明 |
|------------|------|
| `create_hp(str)` | 通过字符串创建高精度整数（也支持 `long long`） |
| `HP_int + HP_int` | 加法 |
| `HP_int - HP_int` | 减法（含负数） |
| `HP_int * HP_int` | 乘法 |
| `HP_int / HP_int` | 除法 |
| `HI_TO_LL(HP_int)` | 转换为 `long long`（超出范围时行为见头文件实现） |

### HP_dec - 高精度小数
| 函数/变量 | 说明 |
|----------|------|
| `create_hp_dec(str)` | 通过字符串创建高精度小数 |
| `precision` | 全局精度控制变量（HP_int 类型） |
| `HP_dec + HP_dec` | 加法 |
| `HP_dec - HP_dec` | 减法 |
| `HP_dec * HP_dec` | 乘法 |
| `HP_dec / HP_dec` | 除法 |

### 类型转换
```cpp
HP_dec HPI_to_HPD(const HP_int& to);   // 整数转小数
HP_int HPD_to_HPI(const HP_dec& to);   // 小数转整数（取整）
```

### HPpow - 快速幂
```cpp
HP_int HPpow(HP_int base, HP_int exponent);
HP_dec HPpow(HP_dec base, HP_int exponent);
```

## 应用场景

- **密码学**：RSA 等大数运算
- **算法竞赛**：处理超过 64 位范围的数据
- **金融计算**：精确货币运算，避免浮点误差
- **科学计算**：需要超高精度的数值运算

## 许可证

本项目采用 **MIT 许可证** 开源，详见 `LICENSE` 文件。

## 贡献与交流

- 欢迎提交 Issue 和 Pull Request
- 更新日志见 `update.md`

## 仓库地址

- Gitee：https://gitee.com/High_P/high-precision
- GitHub：https://github.com/High3p/c-high-precision
