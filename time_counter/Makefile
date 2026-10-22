CC := cc

CFLAGS := -std=c99 -Wall -Wconversion -Wextra -Wpedantic -Wshadow -Wswitch-enum 

SRC_FILES := main.c cmp.c args.c time.c file_reading.c
SRCS := $(addprefix src/, $(SRC_FILES))


.PHONY: all
all:
	$(CC) $(SRCS) -o get_next_bus $(CFLAGS) -Werror -g

.PHONY: warn
warn:
	$(CC) $(SRCS) -o get_next_bus $(CFLAGS)

.PHONY: build
build: 
	$(CC) $(SRCS) -o get_next_bus -std=c99
