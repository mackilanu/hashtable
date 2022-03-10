#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array_1d.h"

/*
 * Minimum working example 2 for array_1d.c.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 *   2018-04-03: v1.1, split into simpler, shorter versions.
 *                     Removed use of automatic, magic, free_handler.
 */

// Struct with month name and number of days.
struct month {
	char *name;
	int days;
};

// Months are stored via void pointers. Convert the given pointer and
// print the dereferenced keys.
static void print_months(const void *data)
{
	// Convert void pointer to pointer to month.
	const struct month *m=data;
	printf("(%s, %d)", m->name, m->days);
}

// Function to free both month structure and char * with name.
static void free_month_struct(void *data)
{
	// Convert void pointer to pointer to month.
	struct month *m=data;
	free(m->name);
	free(m);
}

int main(void)
{
	const char * months[12] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	int month_days[12] = {
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};
			
	// Create an array with 12 positions.
	array_1d *a = array_1d_create(1,12,NULL);

	for (int i=array_1d_low(a); i<=array_1d_high(a); i++) {
		// Allocate memory for a month structure.
		struct month *m=malloc(sizeof(*m));
		// Allocate memory for month name.
		m->name=calloc(strlen(months[i-1])+1,sizeof(char));
		// Copy string.
		strcpy(m->name, months[i-1]);
		// Set days.
		m->days=month_days[i-1];
		// Set key in array.
		array_1d_set_key(a,m,i);
	}
	array_1d_print(a, print_months);
	
        // Empty the array.
	for (int i=array_1d_low(a); i<=array_1d_high(a); i++) {
                if (array_1d_has_key(a,i)) {
                        struct month *v=array_1d_inspect_key(a,i);
                        free_month_struct(v);
                }
        }
	array_1d_kill(a);
	
	return 0;
}
