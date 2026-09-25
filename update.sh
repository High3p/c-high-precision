#!/bin/bash
# HP 一键更新器 v2 - 自动获取文件列表(免维护)
# 用法: 放在 HP 头文件所在文件夹, 终端执行 bash update.sh

BASE_API="https://gitee.com/api/v5/repos/High_P/high-precision/contents/"
BASE_RAW="https://gitee.com/High_P/high-precision/raw/master"

echo "============================================"
echo "   HP 高精度库 - 一键更新器 (自动模式)"
echo "============================================"

# 自动拉取仓库文件清单(只取文件, 跳过文件夹)
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

for f in $FILES; do
    printf "[更新] %s ... " "$f"
    if command -v curl >/dev/null 2>&1; then
        curl -sL --connect-timeout 10 -o "$f" "$BASE_RAW/$f" && echo "[成功]" || echo "[失败]"
    elif command -v wget >/dev/null 2>&1; then
        wget -q --timeout=10 -O "$f" "$BASE_RAW/$f" && echo "[成功]" || echo "[失败]"
    else
        echo "[失败] 未找到 curl 或 wget"
    fi
done

echo "============================================"
echo "  更新完成! 以后新增文件也会自动下载"
echo "============================================"
