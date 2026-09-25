@echo off
chcp 65001 >nul
setlocal
title HP 自动获取器

set "BASE=https://gitee.com/High_P/high-precision/raw/master"
set "DIR=."

if not exist "%DIR%" mkdir "%DIR%"

echo ============================================
echo    HP 高精度库 - 自动获取器
echo    (raw 直连下载, 绕过 zip 风控)
echo    保存目录: %DIR%
echo ============================================
echo.

for %%F in (HPannex.h HPint.h HPdec.h HPmath.h README.md update.md LICENSE .gitignore) do (
    echo [下载] %%F ...
    curl.exe -sL --connect-timeout 10 -o "%DIR%\%%F" "%BASE%/%%F"
    if exist "%DIR%\%%F" (
        echo   [成功] %%F
    ) else (
        echo   [失败] %%F
    )
)

echo.
echo ============================================
echo  完成! 文件已保存到 %DIR% 文件夹
echo  以后想更新, 再双击运行本脚本即可
echo ============================================
pause
