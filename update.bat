@echo off
chcp 65001 >nul
setlocal
title HP 更新器 v2

set "API=https://gitee.com/api/v5/repos/High_P/high-precision/contents/"
set "RAW=https://gitee.com/High_P/high-precision/raw/master"
set "LIST=%TEMP%\hp_files_%RANDOM%.txt"

echo ============================================
echo    HP 高精度库 - 一键更新器 v2 (Windows)
echo    (自动清单 + 自我更新)
echo ============================================

rem ===== 自我更新 =====
curl.exe -sL --connect-timeout 10 -o "%TEMP%\hp_self.bat" "%RAW%/update.bat" >nul 2>&1
if exist "%TEMP%\hp_self.bat" (
    fc /b "%TEMP%\hp_self.bat" "%~f0" >nul 2>&1
    if errorlevel 1 goto :self_update
)
del /q "%TEMP%\hp_self.bat" >nul 2>&1
goto :main

:self_update
copy /y "%TEMP%\hp_self.bat" "%~f0" >nul & del /q "%TEMP%\hp_self.bat" >nul 2>&1 & echo [自我更新] update.bat 已升级, 请重新运行! & pause & exit /b

:main
rem ===== 获取文件列表 (PowerShell 解析 JSON) =====
powershell -NoProfile -Command "$r=Invoke-RestMethod -Uri '%API%' -TimeoutSec 10; $names=@($r | Where-Object {$_.type -eq 'file'} | ForEach-Object {$_.name}); [System.IO.File]::WriteAllLines('%LIST%', $names, (New-Object System.Text.UTF8Encoding($false)))"

if not exist "%LIST%" (
    echo [失败] 无法获取文件列表, 请检查网络
    pause
    exit /b 1
)

echo 发现文件:
type "%LIST%"
echo ----------------------------------------

rem ===== 下载所有文件 (跳过自身) =====
for /f "usebackq delims=" %%F in ("%LIST%") do (
    if /i not "%%F"=="update.bat" (
        echo [更新] %%F ...
        curl.exe -sL --connect-timeout 10 -o "%%F" "%RAW%/%%F" >nul 2>&1 && echo   [成功] || echo   [失败]
    )
)
del /q "%LIST%" >nul 2>&1

echo ============================================
echo  更新完成! 以后新增文件也会自动下载
echo ============================================
pause
