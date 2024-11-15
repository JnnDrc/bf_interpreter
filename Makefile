CC := gcc
DBGFLAGS := -O0 -Wall -Wextra -g
RLSFLAGS := -O3 -Wall
SRC := bfi.c
OBJ := bfi.o
TARGET := bfi

.PHONY: debug clean-w clean-u

$(TARGET): $(OBJ)
	$(CC) $< -o $(TARGET) $(RLSFLAGS)

$(OBJ): $(SRC)
	$(CC) -c $<

debug: $(OBJ)
	$(CC) $< -o bfi-g $(DBGFLAGS)

