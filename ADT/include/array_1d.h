#ifndef __ARRAY_1D_H
#define __ARRAY_1D_H

#include <stdbool.h>
#include "util.h"

/*
 * Declaration of a generic 1D array for the "Datastructures and
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
 */

// ==========PUBLIC DATA TYPES============

// List type.
typedef struct array_1d array_1d;

// ==========DATA STRUCTURE INTERFACE==========

/**
 * array_1d_create() - Create an array without keys.
 * @lo: low index limit.
 * @hi: high index limit.
 * @free_func: A pointer to a function (or NULL) to be called to
 *	       de-allocate memory on remove/kill.
 *
 * The index limits are inclusive, i.e. all indices i such that low <=
 * i <= high are defined.
 * 
 * Returns: A pointer to the new array, or NULL if not enough memory
 * was available.
 */
array_1d *array_1d_create(int lo, int hi, free_function free_func);

/**
 * array_1d_low() - Return the low index limit for the array.
 * @a: array to inspect.
 *
 * Returns: The low index limit.
 */
int array_1d_low(const array_1d *a);

/**
 * array_1d_high() - Return the high index limit for the array.
 * @a: array to inspect.
 *
 * Returns: The high index limit.
 */
int array_1d_high(const array_1d *a);

/**
 * array_1d_inspect_key() - Inspect a key at a given array position.
 * @a: array to inspect.
 * @i: index of position to inspect.
 *
 * Returns: The element key at the specified position. The result is
 *	    undefined if no key are stored at that position.
 */
void *array_1d_inspect_key(const array_1d *a, int i);

/**
 * array_1d_has_key() - Check if a key is set at a given array position.
 * @a: array to inspect.
 * @i: index of position to inspect.
 *
 * Returns: True if a key is set at the specified position, otherwise false.
 */
bool array_1d_has_key(const array_1d *a, int i);

/**
 * array_1d_set_key() - Set a key at a given array position.
 * @a: array to modify.
 * @v: key to set element to, or NULL to clear key.
 * @i: index of position to modify.
 * 
 * If the old element key is non-NULL, calls free_func if it was
 * specified at array creation.
 *
 * Returns: Nothing.
 */
void array_1d_set_key(array_1d *a, void *v, int i);

/**
 * array_1d_kill() - Return memory allocated by array.
 * @a: array to kill.
 * 
 * Iterates over all elements. If free_func was specified at array
 * creation, calls it for every non-NULL element key.
 *
 * Returns: Nothing.
 */
void array_1d_kill(array_1d *a);

/**
 * array_1d_print() - Iterate over the array element and print their keys.
 * @a: Array to inspect.
 * @print_func: Function called for each non-NULL element.
 *
 * Iterates over each position in the array. Calls print_func for each
 * non-NULL key.
 *
 * Returns: Nothing.
 */
void array_1d_print(const array_1d * l, inspect_callback print_func);

#endif
