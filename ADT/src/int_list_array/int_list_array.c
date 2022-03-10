#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "int_list_array.h"

/*
 * Implementation of a generic, undirected list for the
 * "Datastructures and algorithms" courses at the Department of
 * Computing Science, Umea University.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 */

// ===========INTERNAL DATA TYPES============

/*
 * The list is implemented as a static array.
 */
struct list {
	int last_used_pos;
	int *keys;
};

/*
 * Data structure interface
 */

#define ARRAY_MAX_SIZE 10000

/**
 * list_empty() - Create an empty list.
 *
 * Returns: A pointer to the new list.
 */
list *list_empty(void)
{
	// Allocate memory for the list head.
        list *l=malloc(sizeof(list));
        // Allocate memory for the elements.
        l->keys=calloc(ARRAY_MAX_SIZE,sizeof(int));
        // Set last used position.
        l->last_used_pos=-1;
        return l;
}

/**
 * list_is_empty() - Check if a list is empty.
 * @l: List to check.
 *
 * Returns: True if the list is empty, otherwise false.
 */
bool list_is_empty(const list * l)
{
	// List is empty if no elements are used.
	return l->last_used_pos<0;
}

/**
 * list_first() - Return the first position of a list, i.e. the
 *		  position of the first element in the list.
 * @l: List to inspect.
 *
 * Returns: The first position in the given list.
 */
list_position list_first(const list * l)
{
	// First position is always 0.
	return 0;
}

/**
 * list_end() - Return the last position of a list, i.e. the position
 *		after the last element in the list.
 * @l: List to inspect.
 *
 * Returns: The last position in the given list.
 */
list_position list_end(const list * l)
{
	// Last position is position *after* last used element.
	return l->last_used_pos + 1;
}

/**
 * list_next() - Return the next position in a list.
 * @l: List to inspect.
 * @pos: Any valid position except the last in the list.
 *
 * Returns: The position in the list after the given position.
 *	    NOTE: The return key is undefined for the last position.
 */
list_position list_next(const list * l, const list_position pos)
{
	if ( pos == list_end(l) ) {
		// This should really throw an error.
		fprintf(stderr,"list_next: Warning: Trying to navigate "
			"past end of list!");
	}
	return pos + 1;
}

/**
 * list_previous() - Return the previous position in a list.
 * @l: List to inspect.
 * @pos: Any valid position except the first in the list.
 *
 * Returns: The position in the list before the given position.
 *	    NOTE: The return key is undefined for the first position.
 */
list_position list_previous(const list * l, const list_position pos)
{
	if ( pos == list_first( l ) ) {
		// This should really throw an error.
		fprintf(stderr,"list_previous: Warning: Trying to navigate "
			"past beginning of list!\n");
	}
	return pos - 1;
}

/**
 * list_inspect() - Return the key of the element at a given
 *		    position in a list.
 * @l: List to inspect.
 * @pos: Any valid position in the list, except the last.
 *
 * Returns: The integer key stored in the element at postiion pos.
 *	    NOTE: The return key is undefined for the last position.
 */
int list_inspect(const list * l, const list_position pos)
{
	if ( pos == list_end( l )) {
		// This should really throw an error.
		fprintf(stderr,"list_inspace: Warning: Trying to inspect "
			"position at end of list!\n");
	}
	return l->keys[pos];
}

/**
 * list_insert() - Insert a new element with a given key into a list.
 * @l: List to manipulate.
 * @data: Integer key to be inserted into the list.
 * @pos: Position in the list before which the key should be inserted.
 *
 * Creates a new element and inserts it into the list before pos.
 * Stores data in the new element.
 *
 * Returns: The position of the newly created element.
 */
list_position list_insert(list * l, int data, const list_position pos)
{
        // Move elements at position pos and later forward.
        bcopy(l->keys+pos,l->keys+pos+1,
                      sizeof(int)*(l->last_used_pos-pos+1));

        // Set key.
        l->keys[pos]=data;

        // Increment number of used elements.
        l->last_used_pos++;
        
	// Return the position of the new cell.
	return pos;
}

/**
 * list_remove() - Remove an element from a list.
 * @l: List to manipulate.
 * @pos: Position in the list of the element to remove.
 *
 * Removes the element at position pos from the list. If a free_func
 * was registered at list creation, calls it to deallocate the memory
 * held by the element key.
 *
 * Returns: The position after the removed position.
 */
list_position list_remove(list * l, const list_position pos)
{
        // Move elements at position pos and later forward.
        bcopy(l->keys+pos+1,l->keys+pos,sizeof(int)*(l->last_used_pos-pos));

        // Decrement number of used elements.
        l->last_used_pos--;
        
	// Return the position of the next element.
	return pos+1;
}

/*
 * list_kill() - Destroy a given list.
 * @l: List to destroy.
 *
 * Returns all dynamic memory used by the list and its elements. If a
 * free_func was registered at list creation, also calls it for each
 * element to free any user-allocated memory occupied by the element keys.
 *
 * Returns: Nothing.
 */
void list_kill(list * l)
{
        free(l->keys);
	free(l);
}

/*
 * list_print() - Iterate over the list element and print their keys.
 * @l: List to inspect.
 *
 * Iterates over the list and print each stored integer.
 *
 * Returns: Nothing.
 */
void list_print(const list * l)
{
	// Start at the beginning of the list.
	list_position pos = list_first(l);

	while (pos != list_end(l)) {
		// Call print_func with the element key at the
		// current position.
		printf("[%d]\n",list_inspect(l, pos));
		pos = list_next(l, pos);
	}
}
