CC = gcc #compiler
CFLAGS = -Wall -Wextra -g #compiler flags
TARGET= build/mem_alloc #name of executable
SRC = src/main.c src/mem_alloc.c#source code

all:$(TARGET) #default target

$(TARGET): $(SRC) #compiles code @:target <:first prereq
	$(CC) $(CFLAGS) -o $@ $^

clean: #cleans up generated files
	rm -rf build/*