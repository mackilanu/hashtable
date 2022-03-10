#include <stdlib.h>
#include <stdio.h>
#include "int_list_array.h"

/*
 * Minimum working example for int_list.c. Create a list, insert two
 * elements, print list, free list.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *	    Adam Dahlgren Lindstrom (dali@cs.umu.se)
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 */

int main(void)
{
	// Create the list.
	list *l = list_empty();

	// Insert the key 5 first in the list.
	list_insert(l, 5, list_first(l));

	printf("List after inserting one key:\n");
	list_print(l);

	// Insert the key 8 last in the list.
	list_insert(l, 8, list_end(l));

	printf("List after inserting second key at the end:\n");
	list_print(l);

	// Insert the key 2 at the second position in the list.
	list_insert(l, 2, list_next(l, list_first(l)));

	printf("List after inserting a third key in the middle:\n");
	list_print(l);

	// Remove first element.
	list_remove(l, list_first(l));

	printf("List after removing first element:\n");
	list_print(l);
	
	// Done, kill the list.
	list_kill(l);

	return 0;
}

