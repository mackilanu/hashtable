#include <stdio.h>
#include <stdlib.h>

#include "array_2d.h"

/*
 * Implementation of a generic 2D array for the "Datastructures and
 * algorithms" courses at the Department of Computing Science, Umea
 * University.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *
 * Based on earlier code by: Johan Eliasson (johane@cs.umu.se).
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 *   2018-04-03: v1.1, moved freehandler last in create parameter list.
 */

// ===========INTERNAL DATA TYPES============

struct array_2d {
	int low[2]; // Low index limits.
	int high[2]; // High index limits.
	int array_size; // Number of array elements.
	void **keys; // Pointer to where the actual keys are stored.
	free_function free_func; 
};

// ===========INTERNAL FUNCTION IMPLEMENTATIONS============

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
                          free_function free_func)
{
	// Allocate array structure.
	array_2d *a=calloc(1, sizeof(*a));
	// Store index limit.
	a->low[0]=lo1;
	a->low[1]=lo2;
	a->high[0]=hi1;
	a->high[1]=hi2;

	// Number of elements.
	a->array_size = (hi1-lo1+1)*(hi2-lo2+1);

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
 * array_2d_low() - Return the low index limit for the array.
 * @a: array to inspect.
 * @d: dimension number, 1 or 2.
 *
 * Returns: The low index limit for dimension number d.
 */
int array_2d_low(const array_2d *a, int d)
{
	return a->low[d-1];
}

/**
 * array_2d_high() - Return the high index limit for the array.
 * @a: array to inspect.
 * @d: dimension number, 1 or 2.
 *
 * Returns: The high index limit for dimension number d.
 */
int array_2d_high(const array_2d *a, int d)
{
	return a->high[d-1];
}

/**
 * array_2d_linear_index() - Internal function to compute linear index from list
 *			  of indices.
 * @a: array to inspect.
 * @i: First index.
 * @j: Second index.
 *
 * Returns: The linear index corresponding to the list of indices.
 *	    NOTE: The result is undefined if the number of arguments
 *	    or index key are out of bounds.
 */
static int array_2d_linear_index(const array_2d *a,int i, int j)
{
	int rows=a->high[0]-a->low[0]+1;
	int ix=(i-a->low[0])+(j-a->low[1])*rows;
	//fprintf(stderr,"(%d,%d) -> %d\n",i,j,ix);
	return ix;
}

/**
 * array_2d_inspect_key() - Inspect a key at a given array position.
 * @a: array to inspect.
 * @i: First index of position to inspect.
 * @j: Second index of position to inspect.
 *
 * Returns: The element key at the specified position. The result is
 *	    undefined if no key are stored at that position.
 */
void *array_2d_inspect_key(const array_2d *a, int i, int j)
{
	int ix=array_2d_linear_index(a, i, j);
	// Return the key.
	return a->keys[ix];
}

/**
 * array_2d_has_key() - Check if a key is set at a given array position.
 * @a: array to inspect.
 * @i: First index of position to inspect.
 * @j: Second index of position to inspect.
 *
 * Returns: True if a key is set at the specified position, otherwise false.
 */
bool array_2d_has_key(const array_2d *a, int i, int j)
{
	int ix=array_2d_linear_index(a, i, j);
	// Return true if the key is not NULL.
	return a->keys[ix] != NULL;
}

/**
 * array_2d_set_key() - Set a key at a given array position.
 * @a: array to modify.
 * @v: key to set element to, or NULL to clear key.
 * @i: First index of position to modify.
 * @j: Second index of position to modify.
 * 
 * If the old element key is non-NULL, calls free_func if it was
 * specified at array creation.
 *
 * Returns: Nothing.
 */
void array_2d_set_key(array_2d *a, void *v, int i, int j)
{
	int ix=array_2d_linear_index(a, i, j);
	// Call free_func if specified and old element key was non-NULL.
	if (a->free_func != NULL && a->keys[ix] != NULL) {
		a->free_func( a->keys[ix] );
	}
	// Set key.
	a->keys[ix]=v;
}

/**
 * array_2d_kill() - Return memory allocated by array.
 * @a: array to kill.
 * 
 * Iterates over all elements. If free_func was specified at array
 * creation, calls it for every non-NULL element key.
 *
 * Returns: Nothing.
 */
void array_2d_kill(array_2d *a)
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
 * array_2d_print() - Iterate over the array element and print their keys.
 * @a: Array to inspect.
 * @print_func: Function called for each non-NULL element.
 *
 * Iterates over each position in the array. Calls print_func for each
 * non-NULL key.
 *
 * Returns: Nothing.
 */
void array_2d_print(const array_2d *a, inspect_callback print_func)
{
	printf("[\n");
	for (int i=array_2d_low(a,1); i<=array_2d_high(a,1); i++) {
		printf(" [ ");
		for (int j=array_2d_low(a,2); j<=array_2d_high(a,2); j++) { 
			if (array_2d_has_key(a,i,j)) {
				printf("[");
				print_func(array_2d_inspect_key(a,i,j));
				printf("]");
			} else {
				printf("[  ]");
			}
			if (j<array_2d_high(a,2)) {
				printf(", ");
			}
		}
		printf(" ]\n");
	}
	printf(" ]\n");
}
