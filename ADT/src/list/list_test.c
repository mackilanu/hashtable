#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
 * Stub test program for the list implementation in list.c.
 *
 * Author: Niclas Borlin (niclas.borlin@cs.umu.se).
 *
 * Version information:
 *   2018-01-28: v1.0. First public version.
 *   2019-01-23: v1.1. Added file comment. Removed memory cleanup on failure.
 */

/*
 * Verify that a newly created list is empty. Prints an error message
 * to stderr and exits via exit() with an error signal if the test
 * fails.
 */
void empty_list_test()
{
	// Create empty list.
	list *l=list_empty(NULL);

	// Verify that list is empty.
	if (!list_is_empty(l)) {
		// Write error message to stderr.
		fprintf(stderr, "FAIL: New list is not empty!\n");
		// Exit with error message.
		exit(EXIT_FAILURE);
	}

	// The implementation passed the test. Clean up.

        // Deallocate the list structure.
	list_kill(l);
}

/*
 * Verify that a if one element is inserted into an empty list, the
 * list is not empty. Prints an error message to stderr and exits via
 * exit() with an error signal if the test fails.
 */
void one_element_test()
{
	// Create empty list.
	list *l=list_empty(NULL);

	// Create one element.
	int *v=malloc(sizeof(*v));
	*v=4;

	// Insert element first in list.
	list_insert(l, v, list_first(l));

	// Verify that list is NOT empty
	if (list_is_empty(l)) {
		// Write error message to stderr.
		fprintf(stderr, "FAIL: List with one element is empty!\n");
		// Exit with error message.
		exit(EXIT_FAILURE);
	}

	// The implementation passed the test. Clean up.
        
        // Remove all elements from the list.
        while (!list_is_empty(l)) {
                list_pos p=list_first(l);
                int *v=list_inspect(l,p);
                free(v);
                list_remove(l,p);
        }

        // Deallocate the list structure.
	list_kill(l);
}

/*
 * Verify that the key inserted at the end of a empty list can be
 * retrieved via inspect(first()). Prints an error message to stderr
 * and exits via exit() with an error signal if the test fails.
 */
void element_key_test()
{
	// Create empty list.
	list *l=list_empty(NULL);

	// Create element with key 4.
	int *v=malloc(sizeof(*v));
	*v=4;
	// Insert element.
	list_insert(l, v, list_end(l));

	// Verify that key 4 is at the head of the list.
	int *inspected_val=list_inspect(l, list_first(l));
	if (*inspected_val!=4) {
		// Write error message to stderr.
		fprintf(stderr, "FAIL: Expected %d first in list, got %d!\n",
			4,*inspected_val);
		// Exit with error message.
		exit(EXIT_FAILURE);
	}

        // Empty the list.
        while (!list_is_empty(l)) {
                list_pos p=list_first(l);
                int *v=list_inspect(l,p);
                free(v);
                list_remove(l,p);
        }

	// Everything OK, clean up after the test. No memory leaks
	// allowed for passed tests.
	list_kill(l);
}

int main (void)
{
  
	fprintf(stderr,"Running TEST1: empty_list_test(): ");
	empty_list_test();
	fprintf(stderr,"OK.\n");
	fprintf(stderr,"Running TEST2: one_element_test(): ");
	one_element_test();
	fprintf(stderr,"OK.\n");
	fprintf(stderr,"Running TEST3: element_key_test(): ");
	element_key_test();
	fprintf(stderr,"OK.\n");

	// More tests...
	
	fprintf(stderr,"SUCCESS: Implementation passed all tests. Normal exit.\n");
	return 0;
}
