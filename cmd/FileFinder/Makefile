CXX= g++
SRC_DIR= src
INC_DIR= include
OBJ_DIR= ../../make-build/cmd/FileFinder/obj
OUT_DIR= ../../make-build/cmd/FileFinder/out

SRC_FILES= $(shell find $(SRC_DIR) -maxdepth 1 -type f -name *.cpp)
OBJ_FILES= $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

OUT_NAME= FileFinder
OUT_FILE= $(OUT_DIR)/$(OUT_NAME)

all: $(OUT_FILE)

$(OUT_FILE): $(OBJ_FILES)
	mkdir -p $(OUT_DIR)
	$(CXX) -o $(OUT_FILE) $(OBJ_FILES)

$(OBJ_FILES): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -c -o $@ $< -I$(INC_DIR)