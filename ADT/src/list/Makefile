MWE = list_mwe1 list_mwe2

SRC = list.c
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -std=c99 -Wall -I../../include -g

all:	mwe

# Minimum working examples.
mwe:	$(MWE)

# Object file for library
obj:	$(OBJ)

# Clean up
clean:
	-rm -f $(MWE) $(OBJ)

list_mwe1: list_mwe1.c list.c
	gcc -o $@ $(CFLAGS) $^

list_mwe2: list_mwe2.c list.c
	gcc -o $@ $(CFLAGS) $^

memtest1: list_mwe1
	valgrind --leak-check=full --show-reachable=yes $<

memtest2: list_mwe2
	valgrind --leak-check=full --show-reachable=yes $<
