@echo off
echo 🚀 Запуск гри у production режимі...

:: Шлях до білду
set BUILD_PATH="..\Build\Windows\Blaster.exe"

start "" %BUILD_PATH%
pause
