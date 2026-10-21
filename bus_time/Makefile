CC := cc

CFLAGS := -std=c99 -Wall -Wconversion -Wextra -Wpedantic -Wshadow -Wswitch-enum 

SRC_FILES := main.c cmp.c args.c

.PHONY: all
all:
	$(CC) $(SRC_FILES) -o get_next_bus $(CFLAGS) -Werror

warn:
	$(CC) $(SRC_FILES) -o get_next_bus $(CFLAGS)
