MWE = array_1d_mwe1 array_1d_mwe2 array_1d_mwe3 array_1d_mwe4

SRC = array_1d.c
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

array_1d_mwe1: array_1d_mwe1.c array_1d.c
	gcc -o $@ $(CFLAGS) $^

array_1d_mwe2: array_1d_mwe2.c array_1d.c
	gcc -o $@ $(CFLAGS) $^

array_1d_mwe3: array_1d_mwe3.c array_1d.c
	gcc -o $@ $(CFLAGS) $^

array_1d_mwe4: array_1d_mwe4.c array_1d.c
	gcc -o $@ $(CFLAGS) $^

memtest1: array_1d_mwe1
	valgrind --leak-check=full --show-reachable=yes $<

memtest2: array_1d_mwe2
	valgrind --leak-check=full --show-reachable=yes $<

memtest3: array_1d_mwe3
	valgrind --leak-check=full --show-reachable=yes $<

memtest4: array_1d_mwe4
	valgrind --leak-check=full --show-reachable=yes $<
