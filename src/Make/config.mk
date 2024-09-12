ifndef __CONFIG_MK__
export __CONFIG_MK__ = 1

include Make/variables.mk

style:
	@find .. -type f -name "*.tpp" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.cpp" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.hpp" -exec clang-format -n -style=Google {} \;
	@echo "Clang format style check is finished"

c: style_repair

style_repair:
	@find .. -type f -name "*.tpp" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.cpp" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.hpp" -exec clang-format -i -style=Google {} \;
	@echo "Clang format style apply is finished"

dist: 
	tar cvzf ${EXE}.tgz $(BUILD_PATH)

dvi: README.html
	$(OPEN_CMD) $<

README.html: README.md
	pandoc $< -o $@

.PHONY: test all install uninstall clean Dvi dist gcov_report 

leaks: $(BUILD_PATH)/$(TEST_EXE)
	valgrind --leak-check=full --track-origins=yes $(BUILD_PATH)/$(TEST_EXE)

docs:
	@$(MAKE) -C Docs -s 

clean_docs:
	@$(MAKE) -C Docs clean -s

gitconfig: $(CONFIG_PATH)
	git config --global include.path $(CONFIG_PATH)


endif # __CONFIG_MK__