CXX= g++
SRC_DIR= src
INC_DIR= include
OBJ_DIR= ../../make-build/cmd/FileFinder/obj
OUT_DIR= ../../make-build/cmd/FileFinder/out

ARGSPARSER_INC_DIR= ../ArgsParser/include
ARGSPARSER_LIB_DIR= ../../make-build/cmd/ArgsParser/lib
ARGSPARSER_NAME= argsparser
ARGSPARSER_LIB_NAME= $(ARGSPARSER_NAME).a
ARGSPARSER_LIB_FILE= $(ARGSPARSER_LIB_DIR)/$(ARGSPARSER_LIB_NAME)

FUNCS_INC_DIR= ../../funcs/include
FUNCS_LIB_DIR= ../../make-build/funcs/lib
FUNCS_NAME= funcs
FUNCS_LIB_NAME= $(FUNCS_NAME).a
FUNCS_LIB_FILE= $(FUNCS_LIB_DIR)/$(FUNCS_LIB_NAME)

TERMCOLOR_INC_DIR= ../termcolor/include

SRC_FILES= $(shell find $(SRC_DIR) -maxdepth 1 -type f -name *.cpp)
OBJ_FILES= $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

OUT_NAME= FileFinder
OUT_FILE= $(OUT_DIR)/$(OUT_NAME)

all: $(OUT_FILE)

$(OUT_FILE): $(OBJ_FILES) $(FUNCS_LIB_FILE) $(ARGSPARSER_LIB_FILE)
	mkdir -p $(OUT_DIR)
	$(CXX) -o $(OUT_FILE) $(OBJ_FILES) -L $(ARGSPARSER_LIB_DIR) -L $(FUNCS_LIB_DIR) -static -l$(ARGSPARSER_NAME) -l$(FUNCS_NAME)

$(OBJ_FILES): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -c -o $@ $< -I$(INC_DIR) -I$(ARGSPARSER_INC_DIR) -I$(TERMCOLOR_INC_DIR) -I$(FUNCS_INC_DIR) -std=c++17

$(ARGSPARSER_LIB_FILE):
	cd ../ArgsParser && \
	make

$(FUNCS_LIB_FILE):
	cd ../../funcs && \
	make