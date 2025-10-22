# ZimMarketMate

A console-based market simulation game implementing various data structures.

## Building and Running

### Linux/macOS

```bash
make
./zimmate
```

### Windows

#### Option 1: Using the provided batch script

1. Double-click `build.bat` or run it from Command Prompt
2. Run `zimmate.exe`

#### Option 2: Using CMake (Cross-platform)

```cmd
mkdir build
cd build
cmake ..
cmake --build .
./zimmate.exe  # or zimmate.exe on Windows
```

#### Option 3: Manual compilation

If you have MinGW installed:

```cmd
g++ -std=c++17 -O2 -Iinclude src\*.cpp -o zimmate.exe
```

If you have Visual Studio installed:

```cmd
cl /std:c++17 /EHsc /I include src\*.cpp /Fe:zimmate.exe
```

## Requirements

- C++17 compatible compiler
- Windows: MinGW-w64 or Visual Studio 2017+
- Linux/macOS: GCC 7+ or Clang 5+

## Game Commands

Type `help` in the game for available commands.
