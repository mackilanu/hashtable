MWE = stack_mwe1 stack_mwe2

SRC = stack.c
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

stack_mwe1: stack_mwe1.c stack.c
	gcc -o $@ $(CFLAGS) $^

stack_mwe2: stack_mwe2.c stack.c
	gcc -o $@ $(CFLAGS) $^

memtest1: stack_mwe1
	valgrind --leak-check=full --show-reachable=yes $<

memtest2: stack_mwe2
	valgrind --leak-check=full --show-reachable=yes $<
