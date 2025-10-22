cmake_minimum_required(VERSION 3.10)
project(ZimMarketMate)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(zimmate ${SOURCES})

# Compiler-specific options
if(MSVC)
    target_compile_options(zimmate PRIVATE /W4)
else()
    target_compile_options(zimmate PRIVATE -Wall -Wextra -O2)
endif()