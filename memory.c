/*************************************************************************
* Name: Rohan Sharma                                                     *
* Login: rsharma1                                                        *
* Student Number: 639271                                                 *
* COMP30023: Computer Systems Project 1: Memory Manager                  *
*                                                                        *
* memory.c: A file which includes all the functions required when        *
* simulating memory using a linked list representation.                  *
*************************************************************************/

/*-------------------------    Libraries       -------------------------*/
#include "memory.h"
/*----------------------------------------------------------------------*/

/*--------------------  Functional definitions -------------------------*/
/* A function which creates the linked list representing memory.
 * Input: The total size of the memory.
 * Output: A pointer to memory.
 */
memory_t *make_memory(int size) {
	/* Create a new memory representation */
	memory_t *memory;
	memory = (memory_t *)malloc(sizeof(*memory));
	assert(memory != NULL);

	/* Create a new memory segment of size requested */
	segment_t *segment;
	segment = (segment_t *)malloc(sizeof(*segment));
	assert(segment != NULL);

	/* Initialize the segment */
	segment->next = NULL;
	segment->size = size;
	segment->start_address = 0;
	segment->status = FREE;
	segment->order = 0;

	/* Add the segment to memory */
	memory->head = segment;

	return memory;
}

/* A function which combines consecutive free segments in memory.
 * Input: A pointer to memory.
 * Output: A pointer to memory with consecutive free segments combined.
 */
memory_t *combine_free_segments(memory_t *memory) {
	assert(memory != NULL);
	/* Traverse the memory and combine consecutive free segments */
	segment_t *curr, *prev = NULL;
	curr = memory->head;

	while(curr) {
		/* Only run this algorithm if prev and curr are not NULL */
		if(prev && curr) {
			/* Only run this algorithm if prev and curr are free */
			if(prev->status == FREE && curr->status == FREE) {
				/* Combine both prev and curr */
				prev->size += curr->size;
				prev->next = curr->next;
				/* Remove curr from the memory */
				free(curr);
				/* Redo the algo on prev and new curr */
				curr = prev->next;
				continue;
			}
		}
		prev = curr;
		curr = curr->next;
	}
	return memory;
}

/* A function that removes one process from memory and returns it.
 * Input: A pointer to a pointer to memory.
 * Output: A process.
 */
process_t remove_process(memory_t **memory) {
	assert(*memory != NULL);
	/* Remove the process with the largest size.
	 * If there is more than one process which
	 * has the largest size, return the one that
	 * has been in memory longest.
	 */
	int max_size;
	process_t max_process;
	segment_t *max_segment = NULL;

	/* Traverse the memory and find this process */
	segment_t *curr, *prev;
	curr = (*memory)->head;
	while(curr) {
		prev = curr;
		curr = curr->next;
		/* Ensure the segment has a process */
		if(prev->status == RESERVED) {
			/* Find the process with the largest size */
			if(!max_segment || prev->size > max_size) {
				max_size = prev->size;
				max_segment = prev;
			}
			/* If equal size, pick process which has been 
			 * in memory longer. */
			else if(prev->size == max_size) {
				if(prev->order < max_segment->order)  {
					max_segment = prev;
				}
			}
		}
	}

	/* Store the process to return */
	max_process = max_segment->process;
	/* Mark the segment as free */
	max_segment->status = FREE;
	/* Increase the swapped out counter for process */
	max_process.swapped_out++;
	return max_process;
}

/* A function which checks memory if it has a certain amount of free
 * space in consecutive segments.
 * Input: The amount of space, A pointer to memory.
 * Ouput: 1 if yes, 0 if false.
 */
int check_memory(memory_t *memory, int size) {
	assert(memory != NULL);
	/* Initially assume there is not enough space */
	int enough_space = 0;

	/* Traverse the memory and check if there is enough
	 * consecutive space.
	 */
	segment_t *curr, *prev;
	curr = memory->head;
	while(curr) {
		prev = curr;
		curr = curr->next;
		if(prev->status == FREE && prev->size >= size) {
			enough_space = 1;
			break;
		}
	}
	return enough_space;
}

/* A function which frees memory after it is finished being used.
 * Input: Pointer to memory.
 * Output: None, remember to set memory to NULL to avoid misuse.
 */
void free_memory(memory_t *memory) {
	assert(memory != NULL);
	segment_t *curr, *prev;
	curr = memory->head;
	while(curr) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(memory);
}

/* A function which returns the summary of the memory.
 * Input: Pointer to memory.
 * Output: A structure containing the summary of the memory.
 */
memory_summary_t memory_summary(memory_t *memory) {
	assert(memory != NULL);
	/* Create + initialize a memory summary structure */
	memory_summary_t summary;
	summary.processes = summary.holes = summary.reserved_memory = 0;

	/* Traverse memory and build a summary */
	segment_t *curr, *prev;
	curr = memory->head;
	while(curr) {
		prev = curr;
		curr = curr->next;
		if(prev->status == FREE) {
			summary.holes++;
		} 
		else {
			summary.processes++;
			summary.reserved_memory += prev->size;
		}
	}
	return summary;
}
/*----------------------------------------------------------------------*/