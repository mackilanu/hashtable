#ifndef __INT_LIST_ARRAY_H
#define __INT_LIST_ARRAY_H

#include <stdbool.h>
#include "util.h"

/*
 * Declaration of a undirected list for storing integers for the
 * "Datastructures and algorithms" courses at the Department of
 * Computing Science, Umea University. The implementation uses a
 * static array. After use, the function list_kill must be called to
 * de-allocate the dynamic memory used by the list itself. The
 * implementation is a written a code copy specialization of the
 * generic list to provide a simpler starting data structure than the
 * generic list.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *
 * Version information:
 *   2018-03-26: v1.0, first public version.
 */

// ==========PUBLIC DATA TYPES============
// List type.
typedef struct list list;

// List position type.
typedef int list_position;

// ==========DATA STRUCTURE INTERFACE==========

/**
 * list_empty() - Create an empty list.
 *
 * Returns: A pointer to the new list.
 */
list *list_empty(void);

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
list_position list_first(const list *l);

/**
 * list_end() - Return the last position of a list, i.e. the position
 *		after the last element in the list.
 * @l: List to inspect.
 *
 * Returns: The last position in the given list.
 */
list_position list_end(const list *l);

/**
 * list_next() - Return the next position in a list.
 * @l: List to inspect.
 * @pos: Any valid position except the last in the list.
 *
 * Returns: The position in the list after the given position.
 *	    NOTE: The return key is undefined for the last position.
 */
list_position list_next(const list *l, const list_position pos);

/**
 * list_previous() - Return the previous position in a list.
 * @l: List to inspect.
 * @pos: Any valid position except the first in the list.
 *
 * Returns: The position in the list before the given position.
 *	    NOTE: The return key is undefined for the first position.
 */
list_position list_previous(const list *l, const list_position pos);

/**
 * list_inspect() - Return the key of the element at a given
 *		    position in a list.
 * @l: List to inspect.
 * @pos: Any valid position in the list, except the last.
 *
 * Returns: The integer key stored in the element at postiion pos.
 *	    NOTE: The return key is undefined for the last position.
 */
int list_inspect(const list *l, const list_position pos);

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
list_position list_insert(list *l, int data, const list_position pos);

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
list_position list_remove(list *l, const list_position pos);

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
void list_kill(list *l);

/*
 * list_print() - Iterate over the list element and print their keys.
 * @l: List to inspect.
 *
 * Iterates over the list and print each stored integer.
 *
 * Returns: Nothing.
 */
void list_print(const list *l);

#endif
