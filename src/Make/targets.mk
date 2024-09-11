ifndef __TARGETS_MK__
export __TARGETS_MK__ = 1

include Make/variables.mk

all: $(BUILD_PATH) $(BUILD_PATH)/$(EXE) run

run: 
	@$(BUILD_PATH)/$(EXE)

$(BUILD_PATH)/$(EXE): $(BUILD_PATH)/%.o
	@$(CC) $(CXXFLAGS) -o $@ $^

$(BUILD_PATH)/%.o: $(SRCS) $(HEADERS)
	@$(CC) $(CXXFLAGS) -MMD -c $< -o $@

$(BUILD_PATH):
	@mkdir -p $@

clean: clean_docs
	@rm $(RM_FLAGS) $(TRASH)

reset: clean all

test: $(BUILD_PATH)/$(TEST_EXE) test_run

$(BUILD_PATH)/$(TEST_EXE): $(BUILD_PATH) $(BUILD_PATH)/$(EXE)
	$(CC) $(TESTS_PATH)/*.hpp $(TESTS_PATH)/*.cpp $(LIB) -o $@

test_run:
	./$(BUILD_PATH)/$(TEST_EXE)


gcov_report:
	mkdir bin   
	g++ Tests/*.hpp Tests/*.cpp -lgtest -lrt -lpthread -lsubunit -lm --coverage -o bin/s21_list_test
	./bin/s21_list_test
	lcov --capture --directory bin --output-file bin/test.info
	genhtml -o bin/report bin/test.info 
	open bin/report/index.html 

# gcov_report: clean $(BUILD_PATH) 
# 	$(CC) $(TESTS_PATH)/*.hpp $(TESTS_PATH)/*.cpp $(LIB) --coverage -o $(BUILD_PATH)/$(TEST_EXE)
# 	./$(BUILD_PATH)/$(TEST_EXE)
# 	lcov -t "bin/s21_list_test" -o bin/test.info --no-external -c -d bin
# 	genhtml -o $(BUILD_PATH)/report $(BUILD_PATH)/test.info
# 	open $(BUILD_PATH)/report/index.html
	

# lcov -t $(BUILD_PATH)/$(TEST_EXE) -o $(BUILD_PATH)/test.info --no-external -c -d $(BUILD_PATH)

# TODO
# дореализовать gcov_report таргет и сделать так
# чтобы папка report генерировалась внутри bin (build)

endif # __TARGETS_MK__