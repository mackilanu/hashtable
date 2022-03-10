#ifndef __UTIL_H
#define __UTIL_H

/*
 * Utility function types for deallocating, printing and comparing
 * keys stored by various data types.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *	    Adam Dahlgren Lindstrom (dali@cs.umu.se)
 *
 * Based on earlier code by: Johan Eliasson (johane@cs.umu.se).
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 *   2018-02-06: v1.1, updated explanation for the compare_function.
 */

// Type definition for de-allocator function, e.g. free().
typedef void (*free_function)(void *);

// Type definition for read-only callback for single-key containers,
// used by e.g. print functions.
typedef void (*inspect_callback)(const void *);

// Ditto for dual-key containers.
typedef void (*inspect_callback_pair)(const void *, const void *);

// Type definition for comparison function, used by e.g. table.
//
// Comparison functions should return keys that indicate the order
// of the arguments. If the first argument is considered less/lower
// than the second, a negative key should be returned. If the first
// argument is considered more/higher than the second, a positive key
// should be returned. If the arguments are considered equal, a zero
// key should be returned.
typedef int compare_function(const void *,const void *);

#endif
