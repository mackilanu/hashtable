#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

/*
 * Minimum working example for stack.c.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *	    Adam Dahlgren Lindstrom (dali@cs.umu.se)
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 *   2018-04-03: v1.1, split into versions with/without memhandler.
 */

// Integers are stored via int pointers stored as void pointers.
// Convert the given pointer and print the dereferenced key.
static void print_ints(const void *data)
{
	printf("[%d]", *(int*)data);
}

int main(void)
{
	// Create the stack.
	stack *s=stack_empty(NULL);
	
	for (int i=1; i<=3; i++) {
		// Allocate memory for one int.
		int *v = malloc(sizeof(*v));
		// Set key.
		*v=i;
		// Push key on stack.
		s=stack_push(s,v);
	}

	printf("--STACK before popping--\n");
	stack_print(s, print_ints);

	// Get key on top of stack.
	int *v=stack_top(s);
	// Pop element from stack.
	s=stack_pop(s);
	// Free key
	free(v);

	printf("--STACK after popping--\n");
	stack_print(s, print_ints);

	// Now we must empty the stack and free each key ourselves.
	while (!stack_is_empty(s)) {
		// Get key from top of stack.
		int *v=stack_top(s);
		// Pop element from stack.
		s=stack_pop(s);
		// Free key
		free(v);
	}
	// Finally, destroy the bare stack.
	stack_kill(s);
	
	return 0;
}
