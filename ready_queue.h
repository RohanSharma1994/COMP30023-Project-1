/*************************************************************************
* Name: Rohan Sharma                                                     *
* Login: rsharma1                                                        *
* Student Number: 639271                                                 *
* COMP30023: Computer Systems Project 1: Memory Manager                  *
*                                                                        *
* ready_queue.h: A header file which defines the data structures and     *
* functional prototypes which will be used by the ready_queue.c          *
*************************************************************************/
#ifndef READY_QUEUE_H
#define READY_QUEUE_H

/*-------------------------    Libraries       -------------------------*/
#include "process.h"
#include <stdlib.h>
#include <assert.h>
/*----------------------------------------------------------------------*/

/*-------------------------    Constants       -------------------------*/
/* The amount of times the process can be loaded out
 * out of memory before not being allowed to be requeued.
 */
#define LIMIT 3
/*----------------------------------------------------------------------*/

/*-------------------------    Data structure  -------------------------*/
/* Represents a node in the ready queue.
 * process: The process in the node.
 * next: A pointer to the next node.
 */
typedef struct node_s node_t;

struct node_s {
	process_t process;
	node_t *next;
};

/* Represents a ready queue.
 * head: A pointer to the first node.
 * foot: A pointer to the last node.
 */
typedef struct {
	node_t *head;
	node_t *foot;
} ready_queue_t;
/*----------------------------------------------------------------------*/

/*--------------------  Functional prototypes  -------------------------*/
/* A function which creates a new ready queue.
 * Input: None.
 * Output: A pointer to the ready queue.
 */
ready_queue_t *make_ready_queue(void);

/* A function which checks if the ready queue is empty.
 * Input: A pointer to the ready queue.
 * Output: 1 or 0.
 */
int is_empty(ready_queue_t *);

/* A function which queues a process in the ready queue.
 * Input: A pointer to the ready queue, the process.
 * Output: A pointer to the updated ready queue.
 */
ready_queue_t *queue_process(ready_queue_t *, process_t);

/* A function which dequeues a process from the ready queue.
 * Input: A pointer to a pointer to the ready queue.
 * Output: A process.
 */
process_t dequeue_process(ready_queue_t **);

/* A function which frees the ready queue.
 * Input: A pointer to the ready queue.
 * Output: None, remember to set the pointer to NULL to 
 * avoid misuse.
 */
void free_ready_queue(ready_queue_t *);
#endif
/*----------------------------------------------------------------------*/