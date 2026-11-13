CFLAGS := -O4 -std=c99 -Wall -Wconversion -Wextra -Wpedantic -Wshadow -Wswitch-enum 

BIN_NAME := next-event-time

filenames := menu main cmp args time file_reading string_read memory_safety printing
SRC_FILES := $(addsuffix .c, $(filenames))
SRCS := $(addprefix src/, $(SRC_FILES))


.PHONY: all
all:
	$(CC) $(SRCS) -o $(BIN_NAME) $(CFLAGS) -Werror -g

.PHONY: warn
warn:
	$(CC) $(SRCS) -o $(BIN_NAME)

.PHONY: build
build: 
	$(CC) $(SRCS) -o $(BIN_NAME) -std=c99

install: 
	mv $(BIN_NAME) /usr/bin/$(BIN_NAME)

clean:
	rm $(BIN_NAME);

test:
	valgrind --leak-check=full --log-file=val.log --show-leak-kinds=all ./next-event-time --path example.txt    
