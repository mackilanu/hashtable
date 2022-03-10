#include <stdio.h>
#include <stdlib.h>

#include "array_1d.h"

/*
 * Implementation of a generic 1D array for the "Datastructures and
 * algorithms" courses at the Department of Computing Science, Umea
 * University.
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

struct array_1d {
	int low; // Low index limit.
	int high; // High index limit.
	int array_size; // Number of array elements.
	void **keys; // Pointer to where the actual keys are stored.
	free_function free_func; 
};

// ===========INTERNAL FUNCTION IMPLEMENTATIONS============

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
array_1d *array_1d_create(int lo, int hi, free_function free_func)
{
	// Allocate array structure.
	array_1d *a=calloc(1, sizeof(*a));
	// Store index limit.
	a->low=lo;
	a->high=hi;

	// Number of elements.
	a->array_size = hi-lo+1;

	// Store free function.
	a->free_func=free_func;
	
	a->keys=calloc(a->array_size, sizeof(void *));
	
	// Check whether the allocation succeeded.
	if (a->keys == NULL) {
		free(a);
		a=NULL;
	}
	return a;
}

/**
 * array_1d_low() - Return the low index limit for the array.
 * @a: array to inspect.
 *
 * Returns: The low index limit.
 */
int array_1d_low(const array_1d *a)
{
	return a->low;
}

/**
 * array_1d_high() - Return the high index limit for the array.
 * @a: array to inspect.
 *
 * Returns: The high index limit.
 */
int array_1d_high(const array_1d *a)
{
	return a->high;
}

/**
 * array_1d_inspect_key() - Inspect a key at a given array position.
 * @a: array to inspect.
 * @i: index of position to inspect.
 *
 * Returns: The element key at the specified position. The result is
 *	    undefined if no key are stored at that position.
 */
void *array_1d_inspect_key(const array_1d *a, int i)
{
	int offset=i-array_1d_low(a);
	// Return the key.
	return a->keys[offset];
}

/**
 * array_1d_has_key() - Check if a key is set at a given array position.
 * @a: array to inspect.
 * @i: index of position to inspect.
 *
 * Returns: True if a key is set at the specified position, otherwise false.
 */
bool array_1d_has_key(const array_1d *a, int i)
{
	int offset=i-array_1d_low(a);
	// Return true if the key is not NULL.
	return a->keys[offset] != NULL;
}

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
void array_1d_set_key(array_1d *a, void *v, int i)
{
	int offset=i-array_1d_low(a);
	// Call free_func if specified and old element key was non-NULL.
	if (a->free_func != NULL && a->keys[offset] != NULL) {
		a->free_func( a->keys[offset] );
	}
	// Set key.
	a->keys[offset]=v;
}

/**
 * array_1d_kill() - Return memory allocated by array.
 * @a: array to kill.
 * 
 * Iterates over all elements. If free_func was specified at array
 * creation, calls it for every non-NULL element key.
 *
 * Returns: Nothing.
 */
void array_1d_kill(array_1d *a)
{
	if (a->free_func) {
		// Return user-allocated memory for each non-NULL element.
		for (int i=0; i<a->array_size; i++) {
			if (a->keys[i] != NULL) {
				a->free_func(a->keys[i]);
			}
		}
	}
	// Free actual storage.
	free(a->keys);
	// Free array structure.
	free(a);
}

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
void array_1d_print(const array_1d *a, inspect_callback print_func)
{
	printf("[ ");
	for (int i=array_1d_low(a); i<=array_1d_high(a); i++) {
		if (array_1d_has_key(a,i)) {
			printf("[");
			print_func(array_1d_inspect_key(a,i));
			printf("]");
		} else {
			printf(" []");
		}
		if (i<array_1d_high(a)) {
			printf(", ");
		}
	}
	printf(" ]\n");
}
