# Makefile for LRU Cache with include/ and src/ structure

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude

# Directories
INCLUDE_DIR = include
SRC_DIR = src

# Source files
LIB_SOURCES = $(SRC_DIR)/file_info.cpp $(SRC_DIR)/lru_cache.cpp
LIB_OBJECTS = $(LIB_SOURCES:.cpp=.o)
DEMO_SOURCE = demo.cpp
TARGET = demo

# Build library
liblru.a: $(LIB_OBJECTS)
	ar rcs liblru.a $(LIB_OBJECTS)
	@echo "Library created: liblru.a"

# Build demo
$(TARGET): $(DEMO_SOURCE) liblru.a
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(DEMO_SOURCE) -L. -llru
	@echo "Demo built: $(TARGET)"

# Compile source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run demo
run: $(TARGET)
	./$(TARGET)

# Clean
clean:
	rm -f $(SRC_DIR)/*.o liblru.a $(TARGET) file*.txt

.PHONY: run clean