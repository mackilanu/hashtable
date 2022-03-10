#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list.h"

/*
 * Implementation of a generic queue for the "Datastructures and
 * algorithms" courses at the Department of Computing Science, Umea
 * University.
 *
 * Authors: Niclas Borlin (niclas@cs.umu.se)
 *	    Adam Dahlgren Lindstrom (dali@cs.umu.se)
 *
 * Based on earlier code by: Johan Eliasson (johane@cs.umu.se).
 *
 * Version information:
 *   2018-01-28: v1.0, first public version.
 */

// ===========INTERNAL DATA TYPES============

/*
 * The queue is implemented using the list abstract datatype. Almost
 * everything is done by the list.
 */

struct queue {
	list *elements;
};

// ===========INTERNAL FUNCTION IMPLEMENTATIONS============

/**
 * queue_empty() - Create an empty queue.
 * @free_func: A pointer to a function (or NULL) to be called to
 *	       de-allocate memory on remove/kill.
 *
 * Returns: A pointer to the new queue.
 */
queue *queue_empty(free_function free_func)
{
	// Allocate the queue head.
	queue *q=calloc(1, sizeof(*q));
	// Create an empty list.
	q->elements=list_empty(free_func);

	return q;
}

/**
 * queue_is_empty() - Check if a queue is empty.
 * @q: Queue to check.
 *
 * Returns: True if queue is empty, otherwise false.
 */
bool queue_is_empty(const queue *q)
{
	return list_is_empty(q->elements);
}

/**
 * queue_enqueue() - Put a key at the end of the queue.
 * @q: Queue to manipulate.
 * @v: key (pointer) to be put in the queue.
 *
 * Returns: The modified queue.
 */
queue *queue_enqueue(queue *q, void *v)
{
	list_insert(q->elements, v, list_end(q->elements));
	return q;
}

/**
 * queue_dequeue() - Remove the element at the front of a queue.
 * @q: Queue to manipulate.
 *
 * NOTE: Undefined for an empty queue.
 *
 * Returns: The modified queue.
 */
queue *queue_dequeue(queue *q)
{
	list_remove(q->elements, list_first(q->elements));
	return q;
}

/**
 * queue_front() - Inspect the key at the front of the queue.
 * @q: Queue to inspect.
 *
 * Returns: The key at the top of the queue.
 *	    NOTE: The return key is undefined for an empty queue.
 */
void *queue_front(const queue *q)
{
	return list_inspect(q->elements, list_first(q->elements));
}

/**
 * queue_kill() - Destroy a given queue.
 * @q: Queue to destroy.
 *
 * Return all dynamic memory used by the queue and its elements. If a
 * free_func was registered at queue creation, also calls it for each
 * element to free any user-allocated memory occupied by the element keys.
 *
 * Returns: Nothing.
 */
void queue_kill(queue *q)
{
	list_kill(q->elements);
	free(q);
}

/**
 * queue_print() - Iterate over the queue elements and print their keys.
 * @q: Queue to inspect.
 * @print_func: Function called for each element.
 *
 * Iterates over the queue and calls print_func with the key stored
 * in each element.
 *
 * Returns: Nothing.
 */
void queue_print(const queue *q, inspect_callback print_func)
{
	printf("{ ");
	list_pos pos = list_first(q->elements);
	while (pos != list_end(q->elements)) {
		print_func(list_inspect(q->elements, pos));
		pos = list_next(q->elements, pos);
		if (pos != list_end(q->elements)) {
			printf(", ");
		}
	}
	printf(" }\n");
}
