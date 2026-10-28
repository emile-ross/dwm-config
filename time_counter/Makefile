CC := cc

CFLAGS := -std=c99 -Wall -Wconversion -Wextra -Wpedantic -Wshadow -Wswitch-enum 

BIN_NAME := get-next-event

SRC_FILES := main.c cmp.c args.c time.c file_reading.c string_read.c
SRCS := $(addprefix src/, $(SRC_FILES))


.PHONY: all
all:
	$(CC) $(SRCS) -o $(BIN_NAME) $(CFLAGS) -Werror -g

.PHONY: warn
warn:
	$(CC) $(SRCS) -o $(BIN_NAME) $(CFLAGS)

.PHONY: build
build: 
	$(CC) $(SRCS) -o $(BIN_NAME) -std=c99

install: 
	$(CC) $(SRCS) -o next-event-time -std=c99
	mv next-event-time /usr/bin/next-event-time

