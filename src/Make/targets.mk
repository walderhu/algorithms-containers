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

gcov_report: $(BUILD_PATH) 
	$(CC) $(TESTS_PATH)/*.hpp $(TESTS_PATH)/*.cpp $(LIB) --coverage -o $(BUILD_PATH)/$(TEST_EXE)
	lcov -t $(BUILD_PATH)/$(TEST_EXE) -o $(BUILD_PATH)/test.info --no-external -c -d $(BUILD_PATH)
	genhtml -o $(BUILD_PATH)/report $(BUILD_PATH)/test.info
	open $(BUILD_PATH)/report/index.html


# TODO
# дореализовать gcov_report таргет и сделать так
# чтобы папка report генерировалась внутри bin (build)

endif # __TARGETS_MK__