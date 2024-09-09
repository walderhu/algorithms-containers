CC = g++
CFLAGS = -std=c++17

all: main
	@./main
	@make clean -s

main: main.o
	@$(CC) $(CFLAGS) -o main main.o

main.o: main.cpp s21_list.hpp
	@$(CC) $(CFLAGS) -c main.cpp

clean:
	@rm -rf *.o main