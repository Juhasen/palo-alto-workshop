@echo off
setlocal

:: Compiler detection: MSVC, then Clang, then g++.
:: Run from a Developer Command Prompt for MSVC; its architecture (x86 or x64) is the one tested.
where cl.exe >nul 2>&1
if %ERRORLEVEL% equ 0 goto compile_msvc
where clang++ >nul 2>&1
if %ERRORLEVEL% equ 0 goto compile_clang
where g++ >nul 2>&1
if %ERRORLEVEL% equ 0 goto compile_gxx
echo [ERROR] No C++ compiler found. Open a Developer Command Prompt or put clang++ or g++ on PATH.
exit /b 1

:compile_msvc
echo [MSVC %VSCMD_ARG_TGT_ARCH%] Compiling record_file tests...
cl /nologo /std:c++17 /W4 /WX /EHsc /Iinclude src\record_file.cpp tests\record_file_test.cpp /Fe:record_file_test.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
record_file_test.exe
exit /b %ERRORLEVEL%

:compile_clang
echo [Clang] Compiling record_file tests...
clang++ -std=c++17 -Wall -Wextra -Wconversion -Werror -Iinclude src/record_file.cpp tests/record_file_test.cpp -o record_file_test.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
record_file_test.exe
exit /b %ERRORLEVEL%

:compile_gxx
echo [G++] Compiling record_file tests...
g++ -std=c++17 -Wall -Wextra -Wconversion -Werror -Iinclude src/record_file.cpp tests/record_file_test.cpp -o record_file_test.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
record_file_test.exe
exit /b %ERRORLEVEL%
