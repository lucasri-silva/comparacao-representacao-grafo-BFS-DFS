# -*- MakeFile -*-

# target: dependencies
#         action

CXX      := -gcc
CXXFLAGS := -Wall -Wextra -Werror
BUILD    := ./bin
OBJ_DIR  := $(BUILD)/obj
APP_DIR  := $(BUILD)
TARGET   := a.out
INCLUDE  := -Iinclude/
SRC      :=  $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJECTS := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -g -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -g -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release run

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

run:
	./$(BUILD)/$(TARGET)
