#!/bin/bash
# HP 一键更新器 v5 - 自动获取文件列表 + 自我更新 + CRLF兼容
# 用法: 放在 HP 头文件所在文件夹, 终端执行 bash update.sh

BASE_API="https://gitee.com/api/v5/repos/High_P/high-precision/contents/"
BASE_RAW="https://gitee.com/High_P/high-precision/raw/master"

echo "============================================"
echo "   HP 高精度库 - 一键更新器 v5"
echo "============================================"

# ===== 第一步: 自我更新 =====
if command -v curl >/dev/null 2>&1; then
    curl -sL --connect-timeout 10 -o /tmp/hp_self.sh "$BASE_RAW/update.sh"
else
    wget -q --timeout=10 -O /tmp/hp_self.sh "$BASE_RAW/update.sh"
fi

sed -i 's/\r$//' /tmp/hp_self.sh 2>/dev/null

if [ -s /tmp/hp_self.sh ] && bash -n /tmp/hp_self.sh 2>/dev/null && ! cmp -s /tmp/hp_self.sh "$0"; then
    chmod +x /tmp/hp_self.sh
    cp /tmp/hp_self.sh "$0"
    echo "[自我更新] update.sh 已升级, 用新版重新运行..."
    rm -f /tmp/hp_self.sh
    exec bash "$0"
fi
rm -f /tmp/hp_self.sh

# ===== 第二步: 自动获取文件列表 =====
FILES=$(curl -s "$BASE_API" | python3 -c "
import sys, json
for x in json.load(sys.stdin):
    if x['type'] == 'file':
        print(x['name'])
")

if [ -z "$FILES" ]; then
    echo "[失败] 无法获取文件列表, 请检查网络"
    exit 1
fi

echo "发现文件: $(echo $FILES | tr '\n' ' ')"
echo "----------------------------------------"

# ===== 第三步: 下载所有文件 =====
for f in $FILES; do
    if [ "$f" = "update.sh" ]; then
        continue
    fi
    printf "[更新] %s ... " "$f"
    if command -v curl >/dev/null 2>&1; then
        curl -sL --connect-timeout 10 -o "$f" "$BASE_RAW/$f" && echo "[成功]" || echo "[失败]"
    elif command -v wget >/dev/null 2>&1; then
        wget -q --timeout=10 -O "$f" "$BASE_RAW/$f" && echo "[成功]" || echo "[失败]"
    else
        echo "[失败] 未找到 curl 或 wget"
    fi
    # 转换 CRLF -> LF (保证 Linux 下能正常使用)
    sed -i 's/\r$//' "$f" 2>/dev/null
done

echo "============================================"
echo "  更新完成! 本脚本已自动保持最新"
echo "============================================"
