CXX = g++
CXXFLAGS = -std=c++17 -O2 -Iinclude
SRCDIR = src

# Platform detection
ifeq ($(OS),Windows_NT)
	TARGET = zimmate.exe
	RM = del /Q
else
	TARGET = zimmate
	RM = rm -f
endif

SOURCES = $(wildcard $(SRCDIR)/*.cpp)

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	$(RM) $(TARGET)

.PHONY: all clean
