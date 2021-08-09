FILEFINDER_DIR= FileFinder
ARGSPARSER_DIR= ArgsParser
TERMCOLOR_DIR= termcolor

.PHONY: all FileFinder ArgsParser termcolor

all: termcolor ArgsParser FileFinder

termcolor:
	cd $(TERMCOLOR_DIR) && \
	make

FileFinder:
	cd $(FILEFINDER_DIR) && \
	make

ArgsParser:
	cd $(ARGSPARSER_DIR) && \
	make