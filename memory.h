/*************************************************************************
* Name: Rohan Sharma                                                     *
* Login: rsharma1                                                        *
* Student Number: 639271                                                 *
* COMP30023: Computer Systems Project 1: Memory Manager                  *
*                                                                        *
* memory.h: A header file which defines the data structures and          *
* functional prototypes which will be used by memory.c                   *
*************************************************************************/

/*-------------------------    Libraries       -------------------------*/
#ifndef MEMORY_H
#define MEMORY_H
#include "process.h"
#include <stdlib.h>
#include <assert.h>
/*----------------------------------------------------------------------*/

/*-------------------------    Constants       -------------------------*/
#define FREE -1
#define RESERVED 1
/*----------------------------------------------------------------------*/

/*-------------------------    Data structure  -------------------------*/
/* Represents a segment in memory.
 * status: -1 if free, 1 if reserved.
 * process: The process in the memory segment.
 * start_address: The start address of the segment.
 * size: The size of the memory segment.
 * order: Specifies which order this segment was reserved.
 * next: A pointer to the next segment in memory.
 */
typedef struct segment_s segment_t;

struct segment_s {
	int status;
	process_t process;
	int start_address;
	int size;
	int order;
	segment_t *next;
};

/* Represents the memory.
 * head: A pointer to the first memory segment.
 */
typedef struct {
	segment_t *head;
} memory_t;

/* Provides a summary of the memory.
 * processes: The number of processes in memory.
 * holes: The number of holes in memory.
 * reserved_memory: The total amount of memory reserved.
 */
typedef struct {
	int processes;
	int holes;
	int reserved_memory;
} memory_summary_t;
/*----------------------------------------------------------------------*/

/*--------------------  Functional prototypes  -------------------------*/
/* A function which creates the linked list representing memory.
 * Input: The total size of the memory.
 * Output: A pointer to memory.
 */
memory_t *make_memory(int);

/* A function which combines consecutive free segments in memory.
 * Input: A pointer to memory.
 * Output: A pointer to memory with consecutive free segments combined.
 */
memory_t *combine_free_segments(memory_t *);

/* A function that removes one process from memory and returns it.
 * Input: A pointer to a pointer to memory.
 * Output: A process.
 */
process_t remove_process(memory_t **);

/* A function which checks memory if it has a certain amount of free
 * space in consecutive segments.
 * Input: The amount of space, A pointer to memory.
 * Ouput: 1 if yes, 0 if false.
 */
int check_memory(memory_t*, int);

/* A function which frees memory after it is finished being used.
 * Input: Pointer to memory.
 * Output: None, remember to set memory to NULL to avoid misuse.
 */
void free_memory(memory_t *);

/* A function which returns the summary of the memory.
 * Input: Pointer to memory.
 * Output: A structure containing the summary of the memory.
 */
memory_summary_t memory_summary(memory_t *);
#endif
/*----------------------------------------------------------------------*/