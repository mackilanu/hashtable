MWE = int_list_array_mwe

SRC = int_list_array.c
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

int_list_array_mwe: int_list_array_mwe.c int_list_array.c
	gcc -o $@ $(CFLAGS) $^

memtest: int_list_array_mwe
	valgrind --leak-check=full --show-reachable=yes $<
