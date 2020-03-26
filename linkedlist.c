/*
 * ./linkedlist.c
 * Defines linked list and queue methods.
 * Created: 2020-03-04 20:30
 * Author : Leomar Duran <https://github.com/lduran2>
 * For    : CIS 3207, Spring 2020
 */
#include "linkedlist.h"

/*
 * Creates a new singly linked list node that holds the given data.
 */
Node
*node_new(void *data)
{
	Node *node = malloc(sizeof(Node));	/* create the node */
	node->data = data;	/* place the data in the node */
	node->next = NULL;	/* initially, the next node will be NULL */
	return node;	/* return the result */
} /* end *node_new(void*) */

/**
 * Creates a new FIFO queue.
 */
Queue
*queue_new()
{
	Queue *queue = malloc(sizeof(Queue));	/* create the queue */
	Node *phead = node_new(NULL);	/* create the head pointer */
	queue->phead = phead;	/* set the head pointer */
	queue->tail = phead;	/* the tail is also the head pointer */
	queue->length = (size_t)0;	/* start empty */
} /* end *queue_new() */

/**
 * @returns the length of the queue
 */
size_t
queue_length(Queue *queue)
{
	return queue->length;
} /* end queue_length(Queue*) */

/**
 * Adds a new element at the end of the queue.
 * @params
 *   *queue       : Queue = the queue whereto to add
 *   *new_element : Node  = the node for the new element to add
 */
void
queue_enqueue(Queue *queue, Node *new_element)
{
	/* set the next node of the current tail node */
	queue->tail->next = new_element;
	queue->tail = new_element;	/* set the new tail node */
	++queue->length;	/* increment the length */
} /* end *queue_enqueue(Queue*, Node*) */

/**
 * Removes the element at the head of the queue.
 * @params
 *   *queue : Queue = the queue wherefrom to remove
 * @returns the node dequeued
 */
Node
*queue_dequeue(Queue *queue)
{
	/* copy the element to dequeue */
	Node *dequeued = queue->phead->next;
	/* shift the head pointer to the next node */
	queue->phead->next = dequeued->next;
	--queue->length;	/* decrement the length */
	return dequeued;	/* return the node of the element dequeued */
} /* end *queue_dequeue(Queue*) */

/**
 * @returns the element at the head of the queue.
 * @params
 *   *queue : Queue = the queue wherefrom to peek
 */
Node
*queue_peek_first(Queue *queue)
{
	return queue->phead->next;
} /* end *queue_peek_first(Queue*) */

/**
 * @returns if the given queue is empty.
 */
bool
queue_is_empty(Queue *queue)
{
	return (NULL == queue->phead->next);
} /* end queue_is_empty(Queue*) */

/**
 * @returns if the given queue has a next element.
 */
bool
queue_has_next(Queue *queue)
{
	return (!queue_is_empty(queue));
} /* end queue_has_next(Queue*) */

/**
 * Creates an array copy (NULL terminated) of the queue and stores it
 * in ***parray.
 * @params
 *   *queue    : Queue  = the queue to copy
 *   ***parray : void   = pointer to the destination array
 *                        (NULL terminated)
 *   data_size : size_t = size of the data type in the queue
 */
void
queue_to_array(Queue *queue, void ***parray, size_t data_size)
{
	/* start at the pointer to the head */
	Node *node = queue->phead;	/* current element */
	/* create the array */
	void **local_array = malloc((queue->length + 1) * data_size);
	int k;	/* number of elements iterated so far */

	/* loop through the elements in the queue while counting */
	for (k = 0; node = node->next; ++k) {
		/* store the current element data in the array */
		local_array[k] = node->data;
	} /* end for (; node-> next; ) */

	/* NULL terminate the array, k is now the queue length */
	local_array[k] = NULL;

	/* store in the pointer to the array */
	*parray = local_array;
} /* end queue_to_array(Queue*, void***, size_t) */

