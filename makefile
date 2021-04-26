CC := gcc
CFLAGS := -Wall -Werror -ansi

SRC_DIR := ./src
OBJ_DIR := ./src/obj
BIN_DIR := ./bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJ := $(OBJ_DIR)/main.o $(OBJ_DIR)/Accounts.o $(OBJ_DIR)/io.o $(OBJ_DIR)/Encryption.o $(OBJ_DIR)/Compression.o

build: $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/Pass

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm $(OBJ_DIR)/*.o

win: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/Pass.exe