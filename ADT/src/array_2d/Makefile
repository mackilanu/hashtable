MWE = array_2d_mwe1 array_2d_mwe2

SRC = array_2d.c
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

array_2d_mwe1: array_2d_mwe1.c array_2d.c
	gcc -o $@ $(CFLAGS) $^

array_2d_mwe2: array_2d_mwe2.c array_2d.c
	gcc -o $@ $(CFLAGS) $^

memtest1: array_2d_mwe1
	valgrind --leak-check=full --show-reachable=yes $<

memtest2: array_2d_mwe2
	valgrind --leak-check=full --show-reachable=yes $<
