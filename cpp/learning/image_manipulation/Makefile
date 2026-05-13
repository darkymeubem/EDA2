# cwd do make/run = esta pasta (main.cpp usa caminhos como imgs/...).
# Caminho no repo: cpp/learning/image_manipulation (antes: code-c/learning_cpp/image_manipulation).
PROJ_DIR := $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

CXX := g++
CXXFLAGS := -std=c++17 -g -I./src
# MinGW/MSYS2 grava ImageProcessing.exe; sem .exe o make e scripts (ex. mkimg) não acham o ficheiro.
UNAME_S := $(shell uname -s 2>/dev/null)
ifeq ($(OS),Windows_NT)
TARGET := ImageProcessing.exe
else ifneq ($(findstring MINGW,$(UNAME_S))$(findstring MSYS,$(UNAME_S))$(findstring CYGWIN,$(UNAME_S)),)
TARGET := ImageProcessing.exe
else
TARGET := ImageProcessing
endif
BUILD_DIR := build
SRC_DIR := src
SRCS := $(SRC_DIR)/Image.cpp $(SRC_DIR)/main.cpp $(SRC_DIR)/schrift.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all run clean

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# executa o binário com cwd = pasta do Makefile
run: $(TARGET)
	cd "$(PROJ_DIR)" && ./$(TARGET)

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET) ImageProcessing ImageProcessing.exe
