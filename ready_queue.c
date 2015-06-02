/*************************************************************************
* Name: Rohan Sharma                                                     *
* Login: rsharma1                                                        *
* Student Number: 639271                                                 *
* COMP30023: Computer Systems Project 1: Memory Manager                  *
*                                                                        *
* ready_queue.c: A file which includes all the functions that will be    *
* required when using a ready queue.                                     *
*************************************************************************/

/*-------------------------    Libraries       -------------------------*/
#include "ready_queue.h"
/*----------------------------------------------------------------------*/

/*--------------------  Functional definitions -------------------------*/
/* A function which creates a new ready queue.
 * Input: None.
 * Output: A pointer to the ready queue.
 */
ready_queue_t *make_ready_queue(void) {
	/* Create a new ready queue */
	ready_queue_t *queue;
	queue = (ready_queue_t*)malloc(sizeof(*queue));
	assert(queue != NULL);

	/* Initialize the ready queue */
	queue->head = queue->foot = NULL;

	return queue;
}

/* A function which checks if the ready queue is empty.
 * Input: A pointer to the ready queue.
 * Output: 1 or 0.
 */
int is_empty(ready_queue_t *queue) {
	assert(queue != NULL);
	return (queue->head == NULL);
}

/* A function which queues a process in the ready queue.
 * Input: A pointer to the ready queue, the process.
 * Output: A pointer to the updated ready queue.
 */
ready_queue_t *queue_process(ready_queue_t *queue, process_t process) {
	assert(queue != NULL);
	/* Ensure process has not been swapped out of main
	 * memory LIMIT times.
	 */
	if(process.swapped_out == LIMIT) {
		return queue;
	}
	/* Create a new node to be queued */
	node_t *new;
	new = (node_t *)malloc(sizeof(*new));
	assert(new != NULL);

	/* Initialize the new node */
	new->process = process;
	new->next = NULL;

	/* Queue the new node */
	if(is_empty(queue)) {
		queue->head = queue->foot = new;
	}
	else {
		queue->foot->next = new;
		queue->foot = new;
	}
	return queue;
}

/* A function which dequeues a process from the ready queue.
 * Input: A pointer to a pointer to the ready queue.
 * Output: A process.
 */
process_t dequeue_process(ready_queue_t **queue) {
	assert(*queue != NULL);
	assert(!is_empty(*queue));

	/* Get the node to be removed */
	node_t *remove = (*queue)->head;
	process_t process = remove->process;

	/* Remove this node from the queue */
	/* If this was the only node in the queue */
	if((*queue)->head == (*queue)->foot) {
		(*queue)->head = (*queue)->foot = NULL;
	}
	else {
		(*queue)->head = remove->next;
	}

	/* Free the node and return the process */
	free(remove);
	return process;
}

/* A function which frees the ready queue.
 * Input: A pointer to the ready queue.
 * Output: None, remember to set the pointer to NULL to 
 * avoid misuse.
 */
void free_ready_queue(ready_queue_t *queue) {
	assert(queue != NULL);
	node_t *curr, *prev;
	curr = queue->head;
	while(curr) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(queue);
}
/*----------------------------------------------------------------------*/