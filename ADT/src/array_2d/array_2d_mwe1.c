#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array_2d.h"

/*
 * Minimum working example for array_2d.c.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 *   2018-04-03: v1.1, split into versions with/without memhandler.
 */

// Integers are stored via int pointers stored as void pointers.
// Convert the given pointer and print the dereferenced key.
static void print_ints(const void *data)
{
	printf("%d", *(int*)data);
}

int main(void)
{
	// Create a 4-by-3 array.
	array_2d *a = array_2d_create(1,4,1,3,NULL);

	for (int i=array_2d_low(a,1); i<=array_2d_high(a,1); i++) {
		for (int j=array_2d_low(a,2); j<=array_2d_high(a,2); j++) {
			// Allocate memory for an integer.
			int *v=malloc(sizeof(*v));
			// Set key to square of index.
			*v=i*10+j;
			array_2d_set_key(a,v,i,j);
		}
	}
	array_2d_print(a, print_ints);

        // Empty the array.
	for (int i=array_2d_low(a,1); i<=array_2d_high(a,1); i++) {
		for (int j=array_2d_low(a,2); j<=array_2d_high(a,2); j++) {
                        if (array_2d_has_key(a,i,j)) {
                                int *v=array_2d_inspect_key(a,i,j);
                                free(v);
                        }
                }
        }
	array_2d_kill(a);
	
	return 0;
}
