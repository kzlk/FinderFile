CC := g++
CXXFLAGS := -std=c++20 

SRC_DIR := .
OBJ_DIR := obj
APP_NAME := FileSearcher
$(shell mkdir $(OBJ_DIR))

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

ifeq ($(OS),Windows_NT)
	# Windows
	LIB_EXT := lib
	TARGET := $(APP_NAME).exe
	RM := del /q
	FixPath = $(subst /,\,$1)
else
	# Linux
	LIB_EXT := a
	TARGET := $(APP_NAME)
	RM := rm -f
	FixPath = $1
endif

# Library name 
LIBRARY_NAME := filesearch.$(LIB_EXT)

all: $(LIBRARY_NAME) app

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

# Target for the static library
$(LIBRARY_NAME): $(OBJ_DIR)/FileFinder.o
	ar rcs $@ $^

# Target for the application
app: $(OBJ_DIR)/main.o $(LIBRARY_NAME)
	$(CC) $(CXXFLAGS) $(OBJ_DIR)/main.o -L. -l:$(LIBRARY_NAME) -o $(TARGET)

# Clean
clean:
	$(RM) $(call FixPath,$(OBJ_FILES)) $(LIBRARY_NAME) $(call FixPath,$(TARGET))

