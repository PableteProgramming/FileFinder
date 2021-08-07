#root dir makefile
CMD_DIR= cmd

.PHONY: all cmd

all: cmd

cmd:
	cd $(CMD_DIR) && \
	make