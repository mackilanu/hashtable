#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"

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
 * The list elements are implemented as one-cells with a forward link.
 * The list position is a pointer to the internal cell before the cell
 * with the key.
 */
struct cell {
	struct cell *next;
	void *key;
};


struct dlist {
	struct cell *head;
	free_function free_func;
};

// ===========INTERNAL FUNCTION IMPLEMENTATIONS============

/**
 * dlist_empty() - Create an empty dlist.
 * @free_func: A pointer to a function (or NULL) to be called to
 *	       de-allocate memory on remove/kill.
 *
 * Returns: A pointer to the new list.
 */
dlist *dlist_empty(free_function free_func)
{
	// Allocate memory for the list structure.
	dlist *l = calloc(1, sizeof(*l));

	// Allocate memory for the list head.
	l->head = calloc(1, sizeof(struct cell));
	
	// No elements in list so far.
	l->head->next = NULL;

	// Store the free function.
	l->free_func = free_func;
	
	return l;
}

/**
 * dlist_is_empty() - Check if a dlist is empty.
 * @l: List to check.
 *
 * Returns: True if the list is empty, otherwise false.
 */
bool dlist_is_empty(const dlist *l)
{
	return (l->head->next == NULL);
}

/**
 * dlist_first() - Return the first position of a dlist, i.e. the
 *		   position of the first element in the list.
 * @l: List to inspect.
 *
 * Returns: The first position in the given list.
 */
dlist_pos dlist_first(const dlist *l)
{
	return l->head;
}

/**
 * dlist_next() - Return the next position in a dlist.
 * @l: List to inspect.
 * @p: Any valid position except the last in the list.
 *
 * Returns: The position in the list after the given position.
 *	    NOTE: The return key is undefined for the last position.
 */
dlist_pos dlist_next(const dlist *l, const dlist_pos p)
{
	if ( dlist_is_end(l, p) ) {
		// This should really throw an error.
		fprintf(stderr,"dlist_next: Warning: Trying to navigate "
			"past end of list!");
	}
	return p->next;
}

/**
 * dlist_is_end() - Check if a given position is at the end of a dlist.
 * @l: List to inspect.
 * @p: Any valid position in the list.
 *
 * Returns: True if p is at the end of the list.
 */
bool dlist_is_end(const dlist *l, const dlist_pos p)
{
	return p->next == NULL;
}

/**
 * dlist_inspect() - Return the key of the element at a given
 *		     position in a list.
 * @l: List to inspect.
 * @p: Any valid position in the list, except the last.
 *
 * Returns: Returns the key at the given position as a void pointer.
 *	    NOTE: The return key is undefined for the last position.
 */
void *dlist_inspect(const dlist *l, const dlist_pos p)
{
	if ( dlist_is_end(l,p) ) {
		// This should really throw an error.
		fprintf(stderr,"dlist_inspect: Warning: Trying to inspect "
			"position at end of list!\n");
	}
	return p->next->key;
}

/**
 * dlist_insert() - Insert a new element with a given key into a dlist.
 * @l: List to manipulate.
 * @v: key (pointer) to be inserted into the list.
 * @p: Position in the list before which the key should be inserted.
 *
 * Creates a new element and inserts it into the list before p.
 * Stores data in the new element.
 *
 * Returns: The position of the newly created element.
 */
dlist_pos dlist_insert(dlist *l, void *v, const dlist_pos p)
{
	// Create new element.
	dlist_pos new_pos=calloc(1, sizeof(struct cell));
	// Set key.
	new_pos->key=v;

	// Set links.
	new_pos->next=p->next;
	p->next=new_pos;
	
	return p;
}

/**
 * dlist_remove() - Remove an element from a dlist.
 * @l: List to manipulate.
 * @p: Position in the list of the element to remove.
 *
 * Removes the element at position p from the list. If a free_func
 * was registered at list creation, calls it to deallocate the memory
 * held by the element key.
 *
 * Returns: The position after the removed element.
 */
dlist_pos dlist_remove(dlist *l, const dlist_pos p)
{
	// Cell to remove.
	dlist_pos c=p->next;

	// Link past cell to remove.
	p->next=c->next;

	// Call free_func if registered.
	if(l->free_func != NULL) {
		// Free any user-allocated memory for the key.
		l->free_func(c->key);
	}
	// Free the memory allocated to the cell itself.
	free(c);
	// Return the position of the next element.
	return p;
}

/**
 * dlist_kill() - Destroy a given dlist.
 * @l: List to destroy.
 *
 * Return all dynamic memory used by the list and its elements. If a
 * free_func was registered at list creation, also calls it for each
 * element to free any user-allocated memory occupied by the element keys.
 *
 * Returns: Nothing.
 */
void dlist_kill(dlist *l)
{
	// Use public functions to traverse the list.

	// Start with the first element (will be defined even for an
	// empty list).
	dlist_pos p = dlist_first(l);

	// Remove first element until list is empty.
	while(!dlist_is_empty(l)) {
		p = dlist_remove(l, p);
	}

	// Free the head and the list itself.
	free(l->head);
	free(l);    
}

/**
 * dlist_print() - Iterate over the list element and print their keys.
 * @l: List to inspect.
 * @print_func: Function called for each element.
 *
 * Iterates over the list and calls print_func with the key stored
 * in each element.
 *
 * Returns: Nothing.
 */
void dlist_print(const dlist *l, inspect_callback print_func)
{
	// Start at the beginning of the list.
	dlist_pos p = dlist_first(l);

	printf("( ");
	while (!dlist_is_end(l, p)) {
		// Call print_func with the element key at the
		// current position.
		print_func(dlist_inspect(l, p));
		// Advance to next position.
		p = dlist_next(l, p);
		// Print separator unless at element.
		if (!dlist_is_end(l, p)) {
			printf(", ");
		}
	}
	printf(" )\n");
}
