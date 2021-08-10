#root dir makefile
CMD_DIR= cmd
GUI_DIR= gui
FUNCS_DIR= funcs

.PHONY: all funcs cmd gui

all: cmd gui

cmd:
	cd $(CMD_DIR) && \
	make

gui:
	cd $(GUI_DIR) && \
	make

funcs:
	cd $(FUNCS_DIR) && \
	make