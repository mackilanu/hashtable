MWE = queue_mwe1 queue_mwe2

SRC = queue.c
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

queue_mwe1: queue_mwe1.c queue.c ../list/list.c
	gcc -o $@ $(CFLAGS) $^

queue_mwe2: queue_mwe2.c queue.c ../list/list.c
	gcc -o $@ $(CFLAGS) $^

memtest1: queue_mwe1
	valgrind --leak-check=full --show-reachable=yes $<

memtest2: queue_mwe2
	valgrind --leak-check=full --show-reachable=yes $<
