ifndef TARGETS
export TARGETS = 1

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
	@rm -rf $(TRASH)

test: clean $(BUILD_PATH) $(EXE)
	$(CC) $(TESTS_PATH)/*.hpp $(TESTS_PATH)/*.cpp $(LIB) -o $(BUILD_PATH)/$@
	$(BUILD_PATH)/$@

endif