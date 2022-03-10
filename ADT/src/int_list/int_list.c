#include <stdio.h>
#include <stdlib.h>

#include "int_list.h"

/*
 * Implementation of a generic, undirected list for the
 * "Datastructures and algorithms" courses at the Department of
 * Computing Science, Umea University.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 *   2018-03-26: v1.01, bugfix: Corrected const declaration in remove.
 */

// ===========INTERNAL DATA TYPES============

/*
 * The list elements are implemented as two-cells with forward and
 * backward links and place to store one integer. The list uses two
 * border cells at the start and end of the list.
 */
struct cell {
	struct cell *next;
	struct cell *previous;
	int key;
};

struct list {
	struct cell *top;
	struct cell *bottom;
};

/*
 * Data structure interface
 */

/**
 * list_empty() - Create an empty list.
 *
 * Returns: A pointer to the new list.
 */
list *list_empty(void)
{
	// Allocate memory for the list head.
	list *l = calloc(1, sizeof(list));

	// Allocate memory for the border cells.
	l->top = calloc(1, sizeof(struct cell));
	l->bottom = calloc(1, sizeof(struct cell));

	// Set consistent links between border elements.
	l->top->next = l->bottom;
	l->bottom->previous = l->top;

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
	// List is empty if there are no cells between top and bottom.
	return (l->top->next == l->bottom);
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
	// First position is position of first element.
	return l->top->next;
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
	// Last position is position *after* last element.
	return l->bottom;
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
	return pos->next;
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
	return pos->previous;
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
	return pos->key;
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
	// Allocate memory for a new cell.
	list_position elem = malloc(sizeof(struct cell));

	// Store the key.
	elem->key = data;
	// Add links to/from the new cell.
	elem->next = pos;
	elem->previous = pos->previous;
	pos->previous = elem;
	elem->previous->next = elem;

	// Return the position of the new cell.
	return elem;
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
	// Store return position.
	list_position next_pos = pos->next;
	// Link past this element.
	pos->previous->next = pos->next;
	pos->next->previous = pos->previous;

	// Free the memory allocated to the cell itself.
	free(pos);
	// Return the position of the next element.
	return next_pos;
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
	// Use public functions to traverse the list.

	// Start with the first element (will be defined even for an
	// empty list).
	list_position pos = list_first(l);

	// Remove first element until list is empty.
	while (!list_is_empty(l)) {
		pos = list_remove(l, pos);
	}

	// Free border elements and the list head.
	free(l->top);
	free(l->bottom);
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
