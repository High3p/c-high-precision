# HP — 高精度运算库 (High Precision)

[![Version](https://img.shields.io/badge/version-1.5.5-blue)]()
[![License](https://img.shields.io/badge/license-MIT-green)]()
[![C++](https://img.shields.io/badge/C++-11%2B-orange)]()

[🌍 English](README.md) | 🇨🇳 **中文**

一个纯 C++ 头文件实现的高精度整数与小数运算库：支持任意长度四则运算、快速幂、
精度控制、三角函数与常数计算，并内置 **NTT / Karatsuba 快速乘法**，**无任何外部依赖**。

---

## 主要特性

- **HP_int** — 任意精度整数：`+ - * / %`、负数、比较、快速幂
- **HP_dec** — 任意精度小数，带全局 `precision` 精度控制
- **快速乘法**（按位数自动选择）：
  - `≤ 64` 位 → 朴素算法
  - `64 ~ 1024` 位 → **Karatsuba**
  - `> 1024` 位 → **NTT（数论变换）**，大数相乘性能大幅提升
- **牛顿倒数**（`hp_fixed_inv`）— 用"求倒数 + 乘法"实现快速除法
- **数学函数**：`pow`、`hp_pi`（圆周率）、`hp_e`（自然常数）、`hp_sin` / `hp_cos` / `hp_tan`
- **定点运算辅助**：`hp_fixed`、`hp_fixed_to_dec`、`hp_fixed_mul`、`hp_fixed_div` 等
- **零依赖**：纯头文件，只需 `#include`
- **易用**：工厂函数 `create_hp()` / `create_hp_dec()`，也支持 `HP_int a = 10` 直接赋值
- **一键更新器**：`update.bat`（Windows）/ `update.sh`（Linux/macOS）

## 目录结构

```
high-precision/
├── HPannex.h      # 总入口（伞式头文件，自动包含全部）
├── HPint.h        # 任意精度整数
├── HPdec.h        # 任意精度小数 + 精度控制
├── HPmath.h       # 数学：pow、π、e、sin/cos/tan、定点辅助
├── update.bat     # Windows 一键更新器
├── update.sh      # Linux/macOS 一键更新器
├── update.md      # 更新日志
├── LICENSE        # MIT 许可证
├── README.md      # 说明文档（英文）
└── README_zh.md   # 说明文档（中文）
```

## 安装

### 方式一：直接包含头文件
把 `.h` 文件复制到项目目录，源文件开头写：
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
    cout << a - b << endl;   // 减法（支持负数）
    cout << a * b << endl;   // 乘法（自动 NTT/Karatsuba）
    cout << a / b << endl;   // 除法

    // 快速幂：2^100
    cout << pow(create_hp("2"), create_hp("100")) << endl;

    // 直接赋值 int/long long
    HP_int c = 10;
    c += 5;
    cout << c << endl;       // 15
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

### 数学函数
```cpp
precision = create_hp(100);           // 全局精度（小数位数）

HP_dec pi = hp_pi(100);               // 圆周率 π，100 位
HP_dec e  = hp_e(100);                // 自然常数 e，100 位
HP_dec s  = hp_sin(create_hp_dec("1.5"));   // sin
HP_dec c  = hp_cos(create_hp_dec("1.5"));   // cos
HP_dec t  = hp_tan(create_hp_dec("1.5"));   // tan
```

## API 参考

### HP_int — 高精度整数
| 函数 / 运算符 | 说明 |
|---------------|------|
| `create_hp(str)` | 从字符串创建（也支持 `long long`） |
| `HP_int a = 10` | 直接赋值 |
| `+ - * / %` | 算术（自动快速乘法） |
| `> < == != <= >=` | 比较（含 `long long`） |
| `is_zero()` / `isOdd()` / `is_valid()` | 判断函数 |
| `abs(...)` | 绝对值 |
| `hp_one()` | 返回 1 |
| `hp_div2(x)` | 除以 2 |
| `HI_TO_LL(x)` | 转换为 `long long` |

### HP_dec — 高精度小数
| 函数 / 变量 | 说明 |
|-------------|------|
| `create_hp_dec(str)` | 从字符串创建 |
| `precision` | 全局精度控制变量（`HP_int` 类型） |
| `+ - * /` | 算术（按 `precision` 四舍五入） |
| `> < == != <= >=` | 比较 |
| `hp_round(x, n)` | 四舍五入到 `n` 位小数 |
| `HPI_to_HPD(x)` | 整数转小数 |
| `HPD_to_HPI(x)` | 小数转整数 |

### HPmath — 数学函数
| 函数 | 说明 |
|------|------|
| `pow(HP_int, HP_int)` | 整数快速幂 |
| `pow(HP_dec, HP_int)` | 小数快速幂（负指数 = 求倒数） |
| `hp_pi(digits)` | 圆周率，`digits` 位 |
| `hp_e(digits)` | 自然常数 e |
| `hp_sin(x)` / `hp_cos(x)` / `hp_tan(x)` | 三角函数 |
| `hp_fixed(x, work)` / `hp_fixed_to_dec(X, work)` | 定点转换 |
| `hp_fixed_mul` / `hp_fixed_div` / `hp_fixed_div_small` | 定点运算 |
| `hp_fixed_inv` | **牛顿倒数**（快速除法引擎） |

## 性能

乘法按位数自动切换算法：

| 位数 | 算法 | 说明 |
|------|------|------|
| ≤ 64 | 朴素 | 简单直接 |
| 64 ~ 1024 | Karatsuba | O(n^1.585) |
| > 1024 | NTT | O(n log n)，大幅加速 |

Dev-C++ 实测：计算 **1000 万位** 的 2 的幂（`2^10000000`）仅约 **4.4 秒**
（此前算小得多的 `2^10000` 都要约 800 秒）。

## 应用场景

- **密码学**：RSA 等大数运算
- **算法竞赛**：处理超过 64 位范围的数据
- **金融计算**：精确货币运算，避免浮点误差
- **科学计算**：超高精度常数（π、e 等）

## 许可证

本项目采用 **MIT 许可证** 开源，详见 `LICENSE` 文件。

## 更新日志

完整更新记录见 `update.md`。

## 仓库地址

- Gitee：https://gitee.com/High_P/high-precision
- GitHub：https://github.com/High3p/c-high-precision