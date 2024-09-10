ifndef __CONFIG_MK__
export __CONFIG_MK__ = 1

include Make/variables.mk

style:
	clang-format -n -style=google $(SRC_PATH)/* $(TESTS_PATH)/*

dist: 
	tar cvzf ${EXE}.tgz $(BUILD_PATH)

dvi: README.html
	$(OPEN_CMD) $<

README.html: README.md
	pandoc $< -o $@

.PHONY: test all install uninstall clean Dvi dist gcov_report 

leaks: $(BUILD_PATH)/$(EXE)
	valgrind --leak-check=full --track-origins=yes $(BUILD_PATH)/$(EXE)

docs:
	@$(MAKE) -C Docs -s 

clean_docs:
	@$(MAKE) -C Docs clean -s

CURRENT_DIR := $(shell pwd)
gitconfig-apply: $(CURRENT_DIR)/.gitconfig
	git config --global include.path $(CURRENT_DIR)/.gitconfig


endif # __CONFIG_MK__