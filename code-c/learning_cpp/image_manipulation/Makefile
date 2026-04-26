CXX := g++
CXXFLAGS := -std=c++17 -g -I./src
TARGET := ImageProcessing
BUILD_DIR := build
SRC_DIR := src

SRCS := $(SRC_DIR)/Image.cpp $(SRC_DIR)/main.cpp
OBJS := $(BUILD_DIR)/Image.o $(BUILD_DIR)/main.o

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/Image.o: $(SRC_DIR)/Image.cpp $(SRC_DIR)/Image.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/Image.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET) $(TARGET).exe
