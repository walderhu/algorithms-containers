ifndef __VARIABLES_MK__
export __VARIABLES_MK__ = 1

CC := g++
# CXXFLAGS := -Wall -Wextra -Werror -std=c++11
EXE := s21_list
BUILD_PATH := bin
SRC_PATH := Core
TESTS_PATH := Tests
SRCS := $(wildcard $(SRC_PATH)/*.cpp) 
HEADERS := $(wildcard $(SRC_PATH)/*.hpp)
TRASH := README.html $(BUILD_PATH) $(SRC_PATH)/*.gch
UNAME_S := $(shell uname -s)

DEPS := $(SRCS:.cpp=.d)
-include $(DEPS)

ifeq ($(UNAME_S),Linux)
    OPEN_CMD = xdg-open
	LIB = -lgtest -lrt -lpthread -lsubunit -lm
else ifeq ($(UNAME_S),Darwin)
    OPEN_CMD = open
	LIB = -lgtest
else ifeq ($(UNAME_S),Windows_NT)
    OPEN_CMD = start
endif

RM_FLAGS = --recursive --force
# RM_FLAGS += --verbose

endif # __VARIABLES_MK__