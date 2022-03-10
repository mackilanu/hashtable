#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/*
 * Implementation of a generic, undirected list for the
 * "Datastructures and algorithms" courses at the Department of
 * Computing Science, Umea University.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *	    Adam Dahlgren Lindstrom (dali@cs.umu.se)
 *	    Lars Karlsson (larsk@cs.umu.se)
 *
 * Based on earlier code by: Johan Eliasson (johane@cs.umu.se).
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 */

// ===========INTERNAL DATA TYPES============

/*
 * The list elements are implemented as two-cells with forward and
 * backward links. The list uses two border cells at the start and end
 * of the list.
 */
struct cell {
	struct cell *next;
	struct cell *previous;
	void *key;
};

struct list {
	struct cell *top;
	struct cell *bottom;
	free_function free_func;
};

// ===========INTERNAL FUNCTION IMPLEMENTATIONS============

/**
 * list_empty() - Create an empty list.
 * @free_func: A pointer to a function (or NULL) to be called to
 *	       de-allocate memory on remove/kill.
 *
 * Returns: A pointer to the new list.
 */
list *list_empty(free_function free_func)
{
	// Allocate memory for the list head.
	list *l = calloc(1, sizeof(list));

	// Allocate memory for the border cells.
	l->top = calloc(1, sizeof(struct cell));
	l->bottom = calloc(1, sizeof(struct cell));

	// Set consistent links between border elements.
	l->top->next = l->bottom;
	l->bottom->previous = l->top;

	// Store the free function.
	l->free_func = free_func;

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
list_pos list_first(const list * l)
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
list_pos list_end(const list * l)
{
	// Last position is position *after* last element.
	return l->bottom;
}

/**
 * list_next() - Return the next position in a list.
 * @l: List to inspect.
 * @p: Any valid position except the last in the list.
 *
 * Returns: The position in the list after the given position.
 *	    NOTE: The return key is undefined for the last position.
 */
list_pos list_next(const list * l, const list_pos p)
{
	if ( p == list_end(l) ) {
		// This should really throw an error.
		fprintf(stderr,"list_next: Warning: Trying to navigate "
			"past end of list!");
	}
	return p->next;
}

/**
 * list_previous() - Return the previous position in a list.
 * @l: List to inspect.
 * @p: Any valid position except the first in the list.
 *
 * Returns: The position in the list before the given position.
 *	    NOTE: The return key is undefined for the first position.
 */
list_pos list_previous(const list * l, const list_pos p)
{
	if ( p == list_first( l ) ) {
		// This should really throw an error.
		fprintf(stderr,"list_previous: Warning: Trying to navigate "
			"past beginning of list!\n");
	}
	return p->previous;
}

/**
 * list_inspect() - Return the key of the element at a given
 *		    position in a list.
 * @l: List to inspect.
 * @p: Any valid position in the list, except the last.
 *
 * Returns: Returns the key at the given position as a void pointer.
 *	    NOTE: The return key is undefined for the last position.
 */
void *list_inspect(const list * l, const list_pos p)
{
	if ( p == list_end( l )) {
		// This should really throw an error.
		fprintf(stderr,"list_inspect: Warning: Trying to inspect "
			"position at end of list!\n");
	}
	return p->key;
}

/**
 * list_insert() - Insert a new element with a given key into a list.
 * @l: List to manipulate.
 * @v: key (pointer) to be inserted into the list.
 * @p: Position in the list before which the key should be inserted.
 *
 * Creates a new element and inserts it into the list before p.
 * Stores data in the new element.
 *
 * Returns: The position of the newly created element.
 */
list_pos list_insert(list * l, void *v, const list_pos p)
{
	// Allocate memory for a new cell.
	list_pos elem = malloc(sizeof(struct cell));

	// Store the key.
	elem->key = v;
	// Add links to/from the new cell.
	elem->next = p;
	elem->previous = p->previous;
	p->previous = elem;
	elem->previous->next = elem;

	// Return the position of the new cell.
	return elem;
}

/**
 * list_remove() - Remove an element from a list.
 * @l: List to manipulate.
 * @p: Position in the list of the element to remove.
 *
 * Removes the element at position p from the list. If a free_func
 * was registered at list creation, calls it to deallocate the memory
 * held by the element key.
 *
 * Returns: The position after the removed element.
 */
list_pos list_remove(const list * l, const list_pos p)
{
	// Remember return position.
	list_pos next_pos = p->next;
	// Link past this element.
	p->previous->next = p->next;
	p->next->previous = p->previous;

	// Call free_func if registered.
	if (l->free_func != NULL) {
		// Free any user-allocated memory for the key.
		l->free_func(p->key);
	}
	// Free the memory allocated to the cell itself.
	free(p);
	// Return the position of the next element.
	return next_pos;
}

/**
 * list_kill() - Destroy a given list.
 * @l: List to destroy.
 *
 * Return all dynamic memory used by the list and its elements. If a
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
	list_pos p = list_first(l);

	// Remove first element until list is empty.
	while (!list_is_empty(l)) {
		p = list_remove(l, p);
	}

	// Free border elements and the list head.
	free(l->top);
	free(l->bottom);
	free(l);
}

/**
 * list_print() - Iterate over the list element and print their keys.
 * @l: List to inspect.
 * @print_func: Function called for each element.
 *
 * Iterates over the list and calls print_func with the key stored
 * in each element.
 *
 * Returns: Nothing.
 */
void list_print(const list * l, inspect_callback print_func)
{
	// Start at the beginning of the list.
	list_pos p = list_first(l);

	printf("( ");
	while (p != list_end(l)) {
		// Call print_func with the element key at the
		// current position.
		print_func(list_inspect(l, p));
		// Advance to next position.
		p = list_next(l, p);
		// Print separator unless at element.
		if (p != list_end(l)) {
			printf(", ");
		}
	}
	printf(" )\n");
}
