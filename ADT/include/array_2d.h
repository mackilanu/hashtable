#ifndef __ARRAY_2D_H
#define __ARRAY_2D_H

#include <stdbool.h>
#include "util.h"

/*
 * Declaration of a generic 2D array for the "Datastructures and
 * algorithms" courses at the Department of Computing Science, Umea
 * University. The array stores void pointers, so it can be used to
 * store all types of keys. After use, the function array_kill must
 * be called to de-allocate the dynamic memory used by the array
 * itself. The de-allocation of any dynamic memory allocated for the
 * element keys is the responsibility of the user of the array,
 * unless a free_function is registered in array_create.
 *
 * An element key of NULL is considered to be "no" key.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *
 * Based on earlier code by: Johan Eliasson (johane@cs.umu.se).
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 *   2018-04-03: v1.1, moved freehandler last in create parameter list.
 */

// ==========PUBLIC DATA TYPES============

// List type.
typedef struct array_2d array_2d;

// ==========DATA STRUCTURE INTERFACE==========

/**
 * array_2d_create() - Create an array without keys.
 * @lo1: low index limit for first dimension.
 * @hi1: high index limit for first dimension.
 * @lo2: low index limit for second dimension.
 * @hi2: high index limit for second dimension.
 * @free_func: A pointer to a function (or NULL) to be called to
 *	       de-allocate memory on remove/kill.
 *
 * The index limits are inclusive, i.e. all indices i such that low <=
 * i <= high are defined.
 * 
 * Returns: A pointer to the new array, or NULL if not enough memory
 * was available.
 */
array_2d *array_2d_create(int lo1, int hi1, int lo2, int hi2,
                          free_function free_func);

/**
 * array_2d_low() - Return the low index limit for the array.
 * @a: array to inspect.
 * @d: dimension number, 1 or 2.
 *
 * Returns: The low index limit for dimension number d.
 */
int array_2d_low(const array_2d *a, int d);

/**
 * array_2d_high() - Return the high index limit for the array.
 * @a: array to inspect.
 * @d: dimension number, 1 or 2.
 *
 * Returns: The high index limit for dimension number d.
 */
int array_2d_high(const array_2d *a, int d);

/**
 * array_2d_inspect_key() - Inspect a key at a given array position.
 * @a: array to inspect.
 * @i: first index of position to inspect.
 * @j: second index of position to inspect.
 *
 * Returns: The element key at the specified position. The result is
 *	    undefined if no key are stored at that position.
 */
void *array_2d_inspect_key(const array_2d *a, int i, int j);

/**
 * array_2d_has_key() - Check if a key is set at a given array position.
 * @a: array to inspect.
 * @i: first index of position to inspect.
 * @j: second index of position to inspect.
 *
 * Returns: True if a key is set at the specified position, otherwise false.
 */
bool array_2d_has_key(const array_2d *a, int i, int j);

/**
 * array_2d_set_key() - Set a key at a given array position.
 * @a: array to modify.
 * @v: key to set element to, or NULL to clear key.
 * @i: first index of position to inspect.
 * @j: second index of position to inspect.
 * 
 * If the old element key is non-NULL, calls free_func if it was
 * specified at array creation.
 *
 * Returns: Nothing.
 */
void array_2d_set_key(array_2d *a, void *v, int i, int j);

/**
 * array_2d_kill() - Return memory allocated by array.
 * @a: array to kill.
 * 
 * Iterates over all elements. If free_func was specified at array
 * creation, calls it for every non-NULL element key.
 *
 * Returns: Nothing.
 */
void array_2d_kill(array_2d *a);

/**
 * array_2d_print() - Iterate over the array element and print their keys.
 * @a: Array to inspect.
 * @print_func: Function called for each non-NULL element.
 *
 * Iterates over each position in the array. Calls print_func for each
 * non-NULL key.
 *
 * Returns: Nothing.
 */
void array_2d_print(const array_2d * l, inspect_callback print_func);

#endif
