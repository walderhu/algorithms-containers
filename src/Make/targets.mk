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
	$(CC) $(TESTS_PATH)/*.hpp $(TESTS_PATH)/*.cpp $(LIB) --coverage -o $@

test_run:
	./$(BUILD_PATH)/$(TEST_EXE)

gcov_report: $(BUILD_PATH) $(BUILD_PATH)/$(TEST_EXE) test_run
	lcov --capture --directory $(BUILD_PATH) --output-file $(BUILD_PATH)/test.info
	genhtml -o $(BUILD_PATH)/report $(BUILD_PATH)/test.info 
	open $(BUILD_PATH)/report/index.html 

endif # __TARGETS_MK__