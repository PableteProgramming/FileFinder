#root dir makefile
CMD_DIR= cmd
GUI_DIR= gui

.PHONY: all cmd gui

all: cmd gui

cmd:
	cd $(CMD_DIR) && \
	make

gui:
	cd $(GUI_DIR) && \
	make