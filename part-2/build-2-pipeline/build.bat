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
echo [MSVC %VSCMD_ARG_TGT_ARCH%] Compiling timeout_parser tests...
cl /nologo /std:c++17 /W4 /WX /EHsc /Iinclude src\timeout_parser.cpp tests\timeout_parser_test.cpp /Fe:timeout_parser_test.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
timeout_parser_test.exe
exit /b %ERRORLEVEL%

:compile_clang
echo [Clang] Compiling timeout_parser tests...
clang++ -std=c++17 -Wall -Wextra -Wconversion -Werror -Iinclude src/timeout_parser.cpp tests/timeout_parser_test.cpp -o timeout_parser_test.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
timeout_parser_test.exe
exit /b %ERRORLEVEL%

:compile_gxx
echo [G++] Compiling timeout_parser tests...
g++ -std=c++17 -Wall -Wextra -Wconversion -Werror -Iinclude src/timeout_parser.cpp tests/timeout_parser_test.cpp -o timeout_parser_test.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
timeout_parser_test.exe
exit /b %ERRORLEVEL%
