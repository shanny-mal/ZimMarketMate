CXX = g++
CXXFLAGS = -std=c++17 -O2 -Iinclude
SRCDIR = src
TARGET = zimmate

SOURCES = $(wildcard $(SRCDIR)/*.cpp)

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
