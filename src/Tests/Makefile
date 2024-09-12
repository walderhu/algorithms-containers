CC=gcc
SOURCES=views/main_view.cc main.cc ../../controller/controller.cc ../../brick_game/tetris/backend_tetris.cc ../../brick_game/snake/backend_snake.cc
TEST_SOURCES=brick_game/tetris/backend_tetris.cc brick_game/snake/backend_snake.cc tests/test.cc tests/snake/test_snake.cc tests/tetris/test_tetris.cc
TEST_OBJECTS=$(TEST_SOURCES:.cc=.o)
FLAGS=-Wall -Werror -Wextra -std=c++17 -lstdc++
RESULT=brick_game.out
NCURSES=-lncurses
DIST_DIR=archive
TEST_RESULT=testiks.out
TEST_FLAGS      := -lcheck -lm -lpthread #-lsubunit
GCOV_FLAGS      := -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log
TEST_PARTS=$(wildcard brick_game/tetris/tests/test_parts/*.c)

OS := $(shell uname)
ifeq ($(OS),Linux)
	OPEN= xdg-open report/index.html
	CHECK_LIB = -lgtest -lsubunit -lm -lrt -lpthread -lstdc++
endif

ifeq ($(OS),Darwin)
	OPEN= open report/index.html
	CHECK_LIB = -lgtest -lstdc++
endif


all: install run

%.o: %.cc $(HEADERS_AND_TPP)
	$(CC) -c $(CFLAGS) $< -o $@

dvi:
	$(OPEN_COMMAND) ../dvi/README.html

dist: clean_dist
	cd ../ && mkdir -p ${DIST_DIR}
	cd ../ && cp -rf src/brick_game ${DIST_DIR}/brick_game
	cd ../ && cp -rf src/gui ${DIST_DIR}/gui
	cd ../ && cp -rf src/Makefile ${DIST_DIR}/
	cd ../ && tar -czvf archive.tar.gz ${DIST_DIR}
	cd ../ && rm -rf ${DIST_DIR}

dist_unpack:
	cd ../ && tar -xzvf archive.tar.gz

test: $(TEST_OBJECTS)
	$(CC) $(FLAGS) $^ -o $(TEST_RESULT) $(CHECK_LIB)
	./$(TEST_RESULT)

style_check:
	@find .. -type f -name "*.cc" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@echo "Clang format style check is finished"

style:
	@find .. -type f -name "*.cc" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -i -style=Google {} \;
	@echo "Clang format style apply is finished"

gcov_report: $(TEST_SOURCES)
	$(CC) $(CFLAGS) --coverage $^ $(CHECK_LIB) -o $@
	chmod +x *
	./$@ 
	lcov -t "$@" --ignore-errors mismatch --ignore-errors inconsistent -o $@.info --no-external -c -d .
	genhtml -o report/ $@.info
	$(OPEN)

clean: clean_project clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report clean_dist
	@echo "Clean finished"
clean_project:
	@find .. -type f -name "*.records" -exec rm {} \;
clean_dist:
	@cd ../ && rm -rf archive
	@cd ../ && rm -rf archive.tar.gz
clean_static_lib:
	@find .. -type f -name "*.a" -exec rm {} \;
clean_log:
	@find .. -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find .. -type f -name "*.out" -exec rm {} \;
clean_obj:
	@find .. -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@find .. -type f -name "*.gcda" -exec rm {} \;
	@find .. -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find .. -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report
