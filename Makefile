SRC = ADT/src/array_1d/array_1d.c src/hashtable.c src/main.c
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -std=c99 -Wall -I ADT/include/ -I include/ -g

all:
	$(CC) $(CFLAGS) $(SRC) -o hashtable

obj:
	$(OBJ)

# Clean up
clean:
	-rm -f $(OBJ)