ifndef __VARIABLES_MK__
export __VARIABLES_MK__ = 1

CC := g++ -g
CXXFLAGS := -Wall -Wextra -Werror -std=c++17
EXE := s21_list
TEST_EXE := s21_list_test
BUILD_PATH := build
SRC_PATH := Core
TESTS_PATH := Tests

TRASH := README.html $(BUILD_PATH) $(SRC_PATH)/*.gch 
UNAME_S := $(shell uname -s)
CONFIG_PATH := $(shell pwd)/.gitconfig

SRCS=$(shell find $(SRC_PATH) -type f -name "*.cpp")
HEADERS=$(shell find $(SRC_PATH) -type f -name "*.hpp")

TESTS_SRCS=$(shell find $(TESTS_PATH) -type f -name "*.cpp")
TESTS_HEADERS=$(shell find $(TESTS_PATH) -type f -name "*.hpp")

DEPS := $(SRCS:.cpp=.d)
-include $(DEPS)

ifeq ($(UNAME_S),Linux)
    OPEN_CMD = xdg-open
	LIB = -lgtest -lrt -lpthread -lsubunit -lm --coverage
else ifeq ($(UNAME_S),Darwin)
    OPEN_CMD = open
	LIB = -lgtest --coverage
else ifeq ($(UNAME_S),Windows_NT)
    OPEN_CMD = start
endif

RM_FLAGS = --recursive --force
endif # __VARIABLES_MK__