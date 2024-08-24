CC := gcc
DBGFLAGS := -O0 -Wall -Wextra -g
RLSFLAGS := -O2 -Wall
TARGET := bfi

.PHONY: release debug clean-w clean-u

debug: bfi.o
	$(CC) $< -o $(TARGET) $(DBGFLAGS)

release: bfi.o
	$(CC) $< -o $(TARGET) $(RLSFLAGS)


bfi.o: bfi.c
	$(CC) -c $<

clean-w:
	del /F bfi.o
clean-u:
	rm -f bfi.o
