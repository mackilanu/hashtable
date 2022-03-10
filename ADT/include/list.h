#ifndef __LIST_H
#define __LIST_H

#include <stdbool.h>
#include "util.h"

/*
 * Declaration of a generic, undirected list for the "Datastructures
 * and algorithms" courses at the Department of Computing Science,
 * Umea University. The list stores void pointers, so it can be used
 * to store all types of keys. After use, the function list_kill
 * must be called to de-allocate the dynamic memory used by the list
 * itself. The de-allocation of any dynamic memory allocated for the
 * element keys is the responsibility of the user of the list,
 * unless a free_function is registered in list_empty.
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

// ==========PUBLIC DATA TYPES============

// List type.
typedef struct list list;

// List position type.
typedef struct cell *list_pos;

// ==========DATA STRUCTURE INTERFACE==========

/**
 * list_empty() - Create an empty list.
 * @free_func: A pointer to a function (or NULL) to be called to
 *	       de-allocate memory on remove/kill.
 *
 * Returns: A pointer to the new list.
 */
list *list_empty(free_function free_func);

/**
 * list_is_empty() - Check if a list is empty.
 * @l: List to check.
 *
 * Returns: True if the list is empty, otherwise false.
 */
bool list_is_empty(const list *l);

/**
 * list_first() - Return the first position of a list, i.e. the
 *		  position of the first element in the list.
 * @l: List to inspect.
 *
 * Returns: The first position in the given list.
 */
list_pos list_first(const list *l);

/**
 * list_end() - Return the last position of a list, i.e. the position
 *		after the last element in the list.
 * @l: List to inspect.
 *
 * Returns: The last position in the given list.
 */
list_pos list_end(const list *l);

/**
 * list_next() - Return the next position in a list.
 * @l: List to inspect.
 * @p: Any valid position except the last in the list.
 *
 * Returns: The position in the list after the given position.
 *	    NOTE: The return key is undefined for the last position.
 */
list_pos list_next(const list *l, const list_pos p);

/**
 * list_previous() - Return the previous position in a list.
 * @l: List to inspect.
 * @p: Any valid position except the first in the list.
 *
 * Returns: The position in the list before the given position.
 *	    NOTE: The return key is undefined for the first position.
 */
list_pos list_previous(const list *l, const list_pos p);

/**
 * list_inspect() - Return the key of the element at a given
 *		    position in a list.
 * @l: List to inspect.
 * @p: Any valid position in the list, except the last.
 *
 * Returns: Returns the key at the given position as a void pointer.
 *	    NOTE: The return key is undefined for the last position.
 */
void *list_inspect(const list *l, const list_pos p);

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
list_pos list_insert(list *l, void *v, const list_pos p);

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
list_pos list_remove(const list *l, const list_pos p);

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
void list_kill(list *l);

/**
 * list_print() - Iterate over the list elements and print their keys.
 * @l: List to inspect.
 * @print_func: Function called for each element.
 *
 * Iterates over the list and calls print_func with the key stored
 * in each element.
 *
 * Returns: Nothing.
 */
void list_print(const list *l, inspect_callback print_func);

#endif
