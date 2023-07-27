CC := g++
CXXFLAGS := -std=c++20 

SRC_DIR := .
OBJ_DIR := obj

$(shell mkdir -p $(OBJ_DIR))

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

ifeq ($(OS),Windows_NT)
	# Windows
	TARGET := FileFinder.exe
	RM := del /q
	FixPath = $(subst /,\,$1)
else
	# Linux
	TARGET := FileFinder
	RM := rm -f
	FixPath = $1
endif

all: libfilesearch.a app

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

# Target for the static library
libfilesearch.a: $(OBJ_DIR)/FileFinder.o
	ar rcs $@ $^

# Target for the application
app: $(OBJ_DIR)/main.o libfilesearch.a
	$(CC) $(CXXFLAGS) $(OBJ_DIR)/main.o -L. -lfilesearch -o $(TARGET)

# Clean
clean:
	$(RM) $(call FixPath,$(OBJ_FILES)) libfilesearch.a $(call FixPath,$(TARGET))

