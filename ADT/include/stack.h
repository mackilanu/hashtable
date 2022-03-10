#ifndef __STACK_H
#define __STACK_H

#include <stdbool.h>
#include "util.h"

/*
 * Declaration of a generic stack for the "Datastructures and
 * algorithms" courses at the Department of Computing Science, Umea
 * University. The stack stores void pointers, so it can be used to
 * store all types of keys. After use, the function stack_kill must
 * be called to de-allocate the dynamic memory used by the stack
 * itself. The de-allocation of any dynamic memory allocated for the
 * element keys is the responsibility of the user of the stack,
 * unless a free_function is registered in stack_empty.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *	    Adam Dahlgren Lindstrom (dali@cs.umu.se)
 *
 * Based on earlier code by: Johan Eliasson (johane@cs.umu.se).
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 */

// ==========PUBLIC DATA TYPES============

// Stack type.
typedef struct stack stack;

// ==========DATA STRUCTURE INTERFACE==========

/**
 * stack_empty() - Create an empty stack.
 * @free_func: A pointer to a function (or NULL) to be called to
 *	       de-allocate memory on remove/kill.
 *
 * Returns: A pointer to the new stack.
 */
stack *stack_empty(free_function free_func);

/**
 * stack_is_empty() - Check if a stack is empty.
 * @s: Stack to check.
 *
 * Returns: True if stack is empty, otherwise false.
 */
bool stack_is_empty(const stack *s);

/**
 * stack_push() - Push a key on top of a stack.
 * @s: Stack to manipulate.
 * @v: key (pointer) to be put on the stack.
 *
 * Returns: The modified stack.
 */
stack *stack_push(stack *s, void *v);

/**
 * stack_pop() - Remove the element at the top of a stack.
 * @s: Stack to manipulate.
 *
 * NOTE: Undefined for an empty stack.
 *
 * Returns: The modified stack.
 */
stack *stack_pop(stack *s);

/**
 * stack_top() - Inspect the key at the top of the stack.
 * @s: Stack to inspect.
 *
 * Returns: The key at the top of the stack.
 *	    NOTE: The return key is undefined for an empty stack.
 */
void *stack_top(const stack *s);

/**
 * stack_kill() - Destroy a given stack.
 * @s: Stack to destroy.
 *
 * Return all dynamic memory used by the stack and its elements. If a
 * free_func was registered at stack creation, also calls it for each
 * element to free any user-allocated memory occupied by the element keys.
 *
 * Returns: Nothing.
 */
void stack_kill(stack *s);

/**
 * stack_print() - Iterate over the stack elements and print their keys.
 * @s: Stack to inspect.
 * @print_func: Function called for each element.
 *
 * Iterates over the stack and calls print_func with the key stored
 * in each element.
 *
 * Returns: Nothing.
 */
void stack_print(const stack *s, inspect_callback print_func);

#endif
