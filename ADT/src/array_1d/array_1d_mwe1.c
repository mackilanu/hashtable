#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array_1d.h"

/*
 * Minimum working example 1 for array_1d.c.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 *   2018-04-03: v1.1, split into simpler, shorter versions.
 *                     Removed use of automatic, magic, free_handler.
 */

// Integers are stored via int pointers stored as void pointers.
// Convert the given pointer and print the dereferenced key.
static void print_ints(const void *data)
{
	printf("%d", *(int*)data);
}

int main(void)
{
	// Create an array with 6 positions.
	array_1d *a = array_1d_create(1,6,NULL);

	for (int i=array_1d_low(a); i<=array_1d_high(a); i++) {
		// Allocate memory for an integer.
		int *v=malloc(sizeof(*v));
		// Set key to square of index.
		*v=i*i;
		array_1d_set_key(a,v,i);
	}
	array_1d_print(a, print_ints);

        // Empty the array.
	for (int i=array_1d_low(a); i<=array_1d_high(a); i++) {
                if (array_1d_has_key(a,i)) {
                        int *v=array_1d_inspect_key(a,i);
                        free(v);
                }
        }
	array_1d_kill(a);
	
	return 0;
}
