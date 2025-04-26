@echo off

REM Получаем флаги компиляции и линковки из pkg-config
for /f "tokens=*" %%i in ('pkg-config --cflags gtk+-3.0') do set CFLAGS=%%i
for /f "tokens=*" %%i in ('pkg-config --libs gtk+-3.0') do set LIBS=%%i

REM Компиляция программы с полученными флагами
gcc -Wno-format -o weld_fillet_gui main.c temp_function.c temp_function.h -Wno-deprecated-declarations -Wno-format-security -lm %CFLAGS% %LIBS% -mwindows

REM Проверка успешности компиляции
if errorlevel 1 (
    echo Compilation failed
    pause
    exit /b 1
)

echo Compilation was successful. The program is running.
weld_fillet_gui.exe

pause