CC = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11
EXE = s21_list
BUILD_PATH = ./bin
SRC_PATH = ./Core
TESTS_PATH = ./Tests
SRCS = $(wildcard $(SRC_PATH)/*.cxx)
HEADERS = $(wildcard $(SRC_PATH)/*.hxx)
TRASH = README.html $(BUILD_PATH) $(SRC_PATH)/*.gch
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    OPEN_CMD = xdg-open
	LIB = -lgtest -lrt -lpthread -lsubunit -lm
else ifeq ($(UNAME_S),Darwin)
    OPEN_CMD = open
	LIB = -lgtest
else ifeq ($(UNAME_S),Windows_NT)
    OPEN_CMD = start
endif

all: clean $(EXE) run

$(EXE): $(SRCS) $(HEADERS)
	mkdir -p $(BUILD_PATH)
	$(CC) $(CXXFLAGS) $(SRCS) -o $(BUILD_PATH)/$(EXE)

run: $(EXE)
	$(BUILD_PATH)/$(EXE)

clean:
	rm -rf $(TRASH)

style:
	clang-format -n -style=google $(SRC_PATH)/* $(TESTS_PATH)/*

dist: 
	@tar cvzf ${EXE}.tgz $(BUILD_PATH)

dvi: README.html
	$(OPEN_CMD) README.html

README.html: README.md
	pandoc README.md -o README.html

.PHONY: test all install uninstall clean Dvi dist gcov_report 

leaks: $(BUILD_PATH)/$(EXE)
	valgrind --leak-check=full --track-origins=yes $(BUILD_PATH)/$(EXE)

test: clean $(EXE)
	$(CC) $(TESTS_PATH)/*.hxx $(TESTS_PATH)/*.cxx $(LIB) -o $(BUILD_PATH)/test
	$(BUILD_PATH)/test