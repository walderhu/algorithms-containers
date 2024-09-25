CXX := g++
# CXX := g++ --debug # --debug == -g но может замедлить скорость компиляции до 10 раз
# CXXFLAGS := -Wall -Wextra -Werror -std=c++17 -Wpedantic -pipe -O2
EXE := s21_containers
TEST_EXE := s21_containers_test
BUILD_PATH := build
SRC_PATH := Core
TESTS_PATH := Tests

TRASH := $(BUILD_PATH) 
UNAME_S := $(shell uname -s)

SRCS=$(shell find $(SRC_PATH) -type f -name "*.cpp")
TESTS_SRCS =$(shell find $(TESTS_PATH) -type f -name "*.cpp")
# TESTS_SRCS = $(TESTS_PATH)/s21_containers_test.hpp \
# 			$(TESTS_PATH)/s21_containers_test.cpp  \
# 			$(TESTS_PATH)/s21_unordered_set_test.cpp \
# 			$(TESTS_PATH)/s21_unordered_multiset_test.cpp
# TODO вернуть старые тесты
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

all: clean $(BUILD_PATH) $(BUILD_PATH)/$(EXE) run

run: 
	@$(BUILD_PATH)/$(EXE)

$(BUILD_PATH)/%.o: $(SRCS)
	@$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

$(BUILD_PATH)/$(EXE): $(SRCS:$(SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o) $(HEADERS)
	@$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_PATH):
	@mkdir -p $@

clean: 
	@rm -rf $(TRASH)
	@clear

reset: clean all

test:  $(BUILD_PATH)/$(TEST_EXE) test_run

$(BUILD_PATH)/$(TEST_EXE): $(BUILD_PATH) $(BUILD_PATH)/$(EXE)
	@$(CXX) $(TESTS_HEADERS) $(TESTS_SRCS) $(LIB) -o $@

test_run:
	@./$(BUILD_PATH)/$(TEST_EXE)

gcov_report: $(BUILD_PATH) $(BUILD_PATH)/$(TEST_EXE) test_run
	@lcov --capture --directory $(BUILD_PATH) --output-file $(BUILD_PATH)/test.info
	@genhtml -o $(BUILD_PATH)/report $(BUILD_PATH)/test.info 
	@$(MAKE) report_run -s

report_run:
	@open $(BUILD_PATH)/report/index.html 

style:
	@find .. -type f -name "*.cpp" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.hpp" -exec clang-format -n -style=Google {} \;
	@echo "Clang format style check is finished"

c: style_repair

style_repair:
	@find .. -type f -name "*.cpp" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.hpp" -exec clang-format -i -style=Google {} \;
	@echo "Clang format style apply is finished"

.PHONY: test all gcov_report

leaks: $(BUILD_PATH)/$(TEST_EXE)
	valgrind --leak-check=full --track-origins=yes $(BUILD_PATH)/$(TEST_EXE)