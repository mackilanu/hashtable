SRC = ../src/list/list.c ../src/stack/stack.c			\
	../src/array_2d/array_2d.c ../src/table/table.c		\
	../src/table/table2.c ../src/array_1d/array_1d.c	\
	../src/queue/queue.c ../src/dlist/dlist.c
H = ../include/queue.h ../include/dlist.h ../include/array_2d.h	\
	../include/util.h ../include/table.h ../include/list.h	\
	../include/array_1d.h ../include/stack.h

OBJ = $(SRC:.c=.o)

LIB = libdoa.a

CC = gcc
CFLAGS = -std=c99 -Wall -I../include -g

all:	lib

# Library
lib:	$(LIB)

# Object file for library
$(LIB):	$(OBJ) $(H)
	$(AR) r $@ $(OBJ)
	ranlib $@

# Clean up
clean:
	-rm -f $(OBJ)

# Clean up
cleaner:
	-rm -f $(LIB) $(OBJ)

