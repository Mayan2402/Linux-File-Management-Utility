CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

TARGET = filemanager

SOURCES = src/main.cpp src/file_operations.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
