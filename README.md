# HP — 高精度运算库（High Precision）

[![License](https://img.shields.io/badge/license-MIT-green)]()
[![C++](https://img.shields.io/badge/C++-11%2B-orange)]()
[![Dependency](https://img.shields.io/badge/dependencies-none-blue)]()

一个用纯 C++ 头文件实现的高精度整数与小数运算库，支持任意长度的四则运算、取模、快速幂、三角函数与常数计算，**零外部依赖**，只需包含头文件即可使用。

## 简介

传统的 `int`、`long long`、`double` 在处理超大整数或高精度小数时会溢出、丢精度。HP 库用逐位存储的方式保存数值，从底层手写了加减乘除、比较、输入输出与高速乘法，解决溢出和精度丢失问题。

- **`HP_int`**：任意精度整数，支持负数、取模、自增自减与大小比较
- **`HP_dec`**：任意精度小数，支持四则运算、四舍五入与精度控制
- **数学模块**：快速幂、π、自然常数 e、正弦、余弦、正切、指数
- **高速乘法**：朴素 / Karatsuba / NTT 三级自适应，按位数自动选择

## 目录结构

```
high-precision/
├── HPannex.h    # 总入口（伞式头文件，含整数 ↔ 小数转换）
├── HPint.h      # 高精度整数 HP_int 实现（含 NTT 乘法）
├── HPdec.h      # 高精度小数 HP_dec 实现
├── HPmath.h     # 数学函数：幂、π、e、三角、指数
├── update.bat   # Windows 一键更新器
├── update.sh    # Linux / macOS 一键更新器
├── update.md    # 更新日志
├── .gitignore
├── LICENSE      # MIT 开源许可证
└── README.md
```

## 编译要求

- C++11 或更高标准
- 无第三方库依赖
- 头文件方式引入，无需单独编译

## 快速开始

### 引入头文件

把所有 `.h` 文件放到项目目录，源文件开头写：

```cpp
#include "HPannex.h"
using namespace std;
```

### 高精度整数

```cpp
#include "HPannex.h"
using namespace std;

int main() {
    HP_int a = create_hp("123456789012345678901234567890");
    HP_int b = create_hp("98765432109876543210");

    cout << a + b << endl;   // 加法
    cout << a - b << endl;   // 减法（支持负数）
    cout << a * b << endl;   // 乘法
    cout << a / b << endl;   // 除法
    cout << a % b << endl;   // 取模

    // 快速幂：2^100
    cout << pow(create_hp("2"), create_hp("100")) << endl;

    HP_int c = 10;           // 也可直接用整数赋值
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

    cout << d1 + d2 << endl;  // 加法
    cout << d1 - d2 << endl;  // 减法
    cout << d1 * d2 << endl;  // 乘法
    cout << d1 / d2 << endl;  // 除法

    cout << hp_round(d1, 10) << endl;  // 保留 10 位小数
    return 0;
}
```

### 数学函数

```cpp
#include "HPannex.h"
using namespace std;

int main() {
    cout << hp_pi(50) << endl;  // 圆周率，取 50 位
    cout << e(30) << endl;      // 自然常数 e，取 30 位

    HP_dec x = create_hp_dec("0.5");
    cout << hp_sin(x) << endl;  // 正弦
    cout << hp_cos(x) << endl;  // 余弦
    cout << tan(x)    << endl;  // 正切
    cout << exp(x)    << endl;  // 指数 e^x
    return 0;
}
```

## API 参考

### HP_int — 高精度整数

| 接口 | 说明 |
|------|------|
| `create_hp(str)` / `create_hp(ll)` | 用字符串或 `long long` 创建整数 |
| `HP_int a = 10;` | 直接用整数赋值 |
| `a + b` / `a - b` / `a * b` / `a / b` / `a % b` | 四则运算与取模 |
| `a += b` / `-=` / `*=` / `/=` / `%=` | 复合赋值 |
| `++a` / `a++` / `--a` / `a--` | 自增自减 |
| `a == b` / `!=` / `<` / `>` / `<=` / `>=` | 大小比较（支持与 `int`、`long long` 混用） |
| `abs(a)` | 绝对值 |
| `HI_TO_LL(a)` | 转换为 `long long` |
| `cout << a` / `cin >> a` | 输入输出流 |

### HP_dec — 高精度小数

| 接口 | 说明 |
|------|------|
| `create_hp_dec(str)` | 用字符串创建小数 |
| `d1 + d2` / `-` / `*` / `/` | 四则运算 |
| `d1 += d2` / `-=` / `*=` / `/=` | 复合赋值 |
| `++d` / `--d` | 自增自减 |
| `d1 == d2` / `!=` / `<` / `>` / `<=` / `>=` | 大小比较（支持与 `HP_int`、`long long` 混用） |
| `hp_round(d, n)` | 四舍五入到 `n` 位小数 |
| `precision` | 全局精度控制（`HP_int`，默认 `-1`） |
| `cout << d` / `cin >> d` | 输入输出流 |

### 类型转换

```cpp
HP_dec HPI_to_HPD(const HP_int& x);  // 整数转小数
HP_int HPD_to_HPI(const HP_dec& x);  // 小数转整数（取整）
```

### 数学函数

| 函数 | 说明 |
|------|------|
| `pow(HP_int base, HP_int exp)` | 整数快速幂 |
| `pow(HP_dec base, HP_int exp)` | 小数快速幂 |
| `hp_pi(digits)` | 圆周率，`digits` 为有效位数 |
| `e(digits)` | 自然常数 e |
| `hp_sin(x)` / `hp_cos(x)` / `tan(x)` | 三角函数 |
| `exp(x)` | 指数函数 e^x |

## 乘法实现

整数乘法按位数自适应选择三种算法：

| 位数 | 算法 |
|------|------|
| ≤ 64 位 | 朴素竖式乘法 |
| ≤ 1024 位 | Karatsuba 分治乘法 |
| > 1024 位 | NTT 快速数论变换 |

NTT 参数：模数 `NTT_MOD = 2013265921`，原根 `NTT_ROOT = 31`。

## 一键更新

仓库自带更新器，可自动拉取最新头文件：

- **Windows**：双击运行 `update.bat`
- **Linux / macOS**：终端执行 `bash update.sh`

更新器会先自我更新，再按线上文件清单下载全部头文件。

## 应用场景

- **密码学**：RSA 等大数运算
- **算法竞赛**：超过 64 位范围的整数处理
- **精确计算**：需要避免浮点误差的小数运算
- **科学计算**：超高精度常数与三角函数

## 许可证

本项目采用 **MIT 许可证** 开源，详见 `LICENSE`。

## 仓库地址

- Gitee：<https://gitee.com/High_P/high-precision>
- GitHub 镜像：<https://github.com/High3p/c-high-precision>