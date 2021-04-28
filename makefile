CC := gcc
CFLAGS := -Wall -Werror -ansi

SRC_DIR := ./src
OBJ_DIR := ./src/obj
BIN_DIR := ./bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJ := $(OBJ_DIR)/main.o $(OBJ_DIR)/util.o $(OBJ_DIR)/accounts.o $(OBJ_DIR)/io.o $(OBJ_DIR)/encryption.o $(OBJ_DIR)/compression.o

build: $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/Pass.out

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	rm $(OBJ_DIR)/*.o

win: $(OBJ)
	.\WindowsSetup.bat
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/Pass.exe

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@