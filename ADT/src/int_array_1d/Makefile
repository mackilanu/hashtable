MWE = int_array_1d_mwe

SRC = int_array_1d.c
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

int_array_1d_mwe: int_array_1d_mwe.c int_array_1d.c
	gcc -o $@ $(CFLAGS) $^

memtest: int_array_1d_mwe
	valgrind --leak-check=full --show-reachable=yes $<
