CFILES = heap.c heap_test.c
HFILES = heap.h
OPTIONS = -g -std=c99 -pedantic -Wall -Wextra -Werror
OUTPUT = heap_test

all:
	gcc $(OPTIONS) -o $(OUTPUT) $(CFILES)

clean:
	rm -f $(OUTPUT)

run: all
	./$(OUTPUT)
