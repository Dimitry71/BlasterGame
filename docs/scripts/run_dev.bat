@echo off
echo 🔧 Запуск гри в режимі розробки (Unreal Editor)...

:: Шлях до Unreal Editor
set UE_PATH="C:\Program Files\Epic Games\UE_5.3\Engine\Binaries\Win64\UnrealEditor.exe"

:: Шлях до .uproject
set PROJECT_PATH="..\Blaster.uproject"

%UE_PATH% %PROJECT_PATH% -game
pause
