CC := gcc
CFLAGS := -Wall -Wextra -O2
GDB := 


ifeq ($(GDB), true)
	CFLAGS += -g
endif

.PHONY: bfi 

bfi: bfi.c
	$(CC) $^ -o $@ $(CFLAGS)

