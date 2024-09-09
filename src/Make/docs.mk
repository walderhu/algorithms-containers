ifndef __DOCS_MK__
export __DOCS_MK__ = 1

all:
	@doxygen Doxyfile
	@open docs/html/index.html

clean:
	@rm -rf docs

endif # __DOCS_MK__