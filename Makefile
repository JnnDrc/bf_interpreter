CC := gcc
CFLAGS := -Wall -Wextra -O2

.PHONY: bfi 

bfi: bfi.c
	$(CC) $^ -o $@ $(CFLAGS)

