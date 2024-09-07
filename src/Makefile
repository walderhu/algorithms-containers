CC = g++
CXXFLAGS = -Wall -Wextra -O2
SRC_DIR = Core
BIN = main
SRCS = $(wildcard $(SRC_DIR)/*.cxx)
HEADERS = $(wildcard $(SRC_DIR)/*.hxx)

all: clean $(BIN) run

$(BIN): $(SRCS) $(HEADERS)
	@$(CC) $(CXXFLAGS) $(SRCS) -o $(BIN)

run: $(BIN)
	@./$(BIN)

clean:
	@rm -rf $(BIN)