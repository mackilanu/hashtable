#include <stdio.h>
#include <stdlib.h>
#include "int_array_1d.h"

/*
 * Minimum working example for int_array_1d.c.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 */

int main(void)
{
	// Create an array with 6 positions.
	int_array_1d *a = int_array_1d_create(1,6);

	for (int i=int_array_1d_low(a); i<=int_array_1d_high(a); i++) {
		// Store square of index.
		int_array_1d_set_key(a,i*i,i);
		// Print array after setting each key.
		int_array_1d_print(a);
	}
	
	int_array_1d_kill(a);
	
	return 0;
}
