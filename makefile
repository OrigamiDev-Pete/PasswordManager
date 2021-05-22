CC := gcc
CFLAGS := -Wall -Werror -ansi

SRC_DIR := ./src
OBJ_DIR := ./src/obj
BIN_DIR := ./bin

#SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
#OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJ := $(OBJ_DIR)/main.o $(OBJ_DIR)/util.o $(OBJ_DIR)/accounts.o $(OBJ_DIR)/io.o $(OBJ_DIR)/encryption.o $(OBJ_DIR)/compression.o $(OBJ_DIR)/huffman.o

build: $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/main.out

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -g -c $< -o $@

debug: $(BIN_DIR) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -DDEBUG -g -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) -DDEBUG -g -c $(SRC_DIR)/util.c -o $(OBJ_DIR)/util.o
	$(CC) $(CFLAGS) -DDEBUG -g -c $(SRC_DIR)/accounts.c -o $(OBJ_DIR)/accounts.o
	$(CC) $(CFLAGS) -DDEBUG -g -c $(SRC_DIR)/io.c -o $(OBJ_DIR)/io.o
	$(CC) $(CFLAGS) -DDEBUG -g -c $(SRC_DIR)/encryption.c -o $(OBJ_DIR)/encryption.o
	$(CC) $(CFLAGS) -DDEBUG -g -c $(SRC_DIR)/compression.c -o $(OBJ_DIR)/compression.o
	$(CC) $(CFLAGS) -DDEBUG -g -c $(SRC_DIR)/huffman.c -o $(OBJ_DIR)/huffman.o

clean:
	rm $(OBJ_DIR)/*.o

win: $(OBJ)
	.\WindowsSetup.bat
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/main.exe

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@