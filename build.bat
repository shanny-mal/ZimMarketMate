@echo off
echo Building ZimMarketMate for Windows...

REM Check if g++ is available (MinGW)
where g++ >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Using g++ compiler...
    g++ -std=c++17 -O2 -Iinclude src\*.cpp -o zimmate.exe
) else (
    REM Check if cl is available (MSVC)
    where cl >nul 2>nul
    if %ERRORLEVEL% EQU 0 (
        echo Using MSVC compiler...
        cl /std:c++17 /EHsc /I include src\*.cpp /Fe:zimmate.exe
    ) else (
        echo Error: No C++ compiler found. Please install MinGW or Visual Studio.
        pause
        exit /b 1
    )
)

if exist zimmate.exe (
    echo Build successful! Run zimmate.exe to start the game.
) else (
    echo Build failed!
)
pause