ifndef __TARGETS_MK__
export __TARGETS_MK__ = 1

include Make/variables.mk

all: clean $(BUILD_PATH) $(EXE) run

run: 
	@$(BUILD_PATH)/$(EXE)

$(EXE): $(BUILD_PATH)/%.o
	@$(CC) $(CXXFLAGS) -o $(BUILD_PATH)/$@ $^

$(BUILD_PATH)/%.o: $(SRCS) $(HEADERS)
	@$(CC) $(CXXFLAGS) -MMD -c $< -o $@

$(BUILD_PATH):
	@mkdir -p $@

clean: clean_docs
	@rm $(RM_FLAGS) $(TRASH)

test: $(BUILD_PATH)/$(TEST_EXE) test_run

$(BUILD_PATH)/$(TEST_EXE): clean $(BUILD_PATH) $(EXE)
	$(CC) $(TESTS_PATH)/*.hpp $(TESTS_PATH)/*.cpp $(LIB) -o $@

test_run:
	./$(BUILD_PATH)/$(TEST_EXE)

gcov_report: $(BUILD_PATH)/$(TEST_EXE)
	lcov -t $(BUILD_PATH)/$(TEST_EXE) -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html


# TODO
# дореализовать gcov_report таргет и сделать так
# чтобы папка report генерировалась внутри bin (build)

endif # __TARGETS_MK__