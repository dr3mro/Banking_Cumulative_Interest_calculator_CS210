@echo off
setlocal

cd /d "%~dp0"

where make >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    make build
    if errorlevel 1 exit /b %ERRORLEVEL%
    banking.exe
    exit /b %ERRORLEVEL%
)

where g++ >nul 2>&1
if errorlevel 1 (
    echo Error: install GNU Make and MinGW g++, or add them to PATH.
    exit /b 1
)

if not exist build\obj mkdir build\obj

g++ -std=c++17 -Wall -Wextra -pedantic -c rf-banking.cpp -o build\obj\rf-banking.o
if errorlevel 1 exit /b %ERRORLEVEL%

g++ -std=c++17 -Wall -Wextra -pedantic -c rf-bankingMain.cpp -o build\obj\rf-bankingMain.o
if errorlevel 1 exit /b %ERRORLEVEL%

g++ -std=c++17 -Wall -Wextra -pedantic build\obj\rf-banking.o build\obj\rf-bankingMain.o -o banking.exe
if errorlevel 1 exit /b %ERRORLEVEL%

banking.exe
exit /b %ERRORLEVEL%
