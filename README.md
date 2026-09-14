# HP - 高精度运算库 (High Precision)

一个 C++ 高精度整数与小数运算库，支持任意长度的整数和小数四则运算、快速幂、精度控制。

## 功能

- `HP_int`：高精度整数（正负数、加减乘除、快速幂）
- `HP_dec`：高精度小数（四则运算、`precision` 精度控制）
- `HPpow`：快速幂（HP_int / HP_dec / double 三种重载）
- `HI_TO_LL`：HP_int → long long 转换（带溢出检测）

## 快速开始

把 `HPannex.h` 加入 include 路径，然后：

```cpp
#include "HPannex.h"
using namespace std;

int main() {
    HP_int a = create_hp("123456789012345678901234567890");
    HP_int b = create_hp("98765432109876543210");
    cout << a + b << endl;                              // 高精度加法
    cout << HPpow(create_hp("2"), create_hp("100")) << endl;  // 2^100

    HP_dec d1 = create_hp_dec("5.08320474913");
    HP_dec d2 = create_hp_dec("2.562391563502");
    precision = create_hp("2");                        // 小数精度
    cout << d1 * d2 << endl;
    return 0;
}

```
这里输入代码
```
