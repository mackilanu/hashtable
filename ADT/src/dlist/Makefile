MWE = dlist_mwe1 dlist_mwe2

SRC = dlist.c
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -std=c99 -Wall -I../../include -g

all:	mwe

# Minimum working examples.
mwe:	$(MWE)

# Object file for library
obj:	$(OBJ)

clean:
	-rm -f $(MWE) $(OBJ)

dlist_mwe1: dlist_mwe1.c dlist.c
	gcc -o $@ $(CFLAGS) $^

dlist_mwe2: dlist_mwe2.c dlist.c
	gcc -o $@ $(CFLAGS) $^

memtest1: dlist_mwe1
	valgrind --leak-check=full --show-reachable=yes $<

memtest2: dlist_mwe2
	valgrind --leak-check=full --show-reachable=yes $<
