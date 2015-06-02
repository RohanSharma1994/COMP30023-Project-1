/*************************************************************************
* Name: Rohan Sharma                                                     *
* Login: rsharma1                                                        *
* Student Number: 639271                                                 *
* COMP30023: Computer Systems Project 1: Memory Manager                  *
*                                                                        *
* fit_algorithms.c: The file which includes the functions required to    *
* perform all the fit algorithms.                                        *
*************************************************************************/

/*-------------------------    Libraries       -------------------------*/
#include "fit_algorithms.h"
/*----------------------------------------------------------------------*/

/*------------------------- Functional definitions----------------------*/
/* A function which performs the first fit algorithm.
 * Input: The pointer to memory, and the process to load.
 * Output: A pointer to memory.
 */
memory_t *first_fit(memory_t *memory, process_t process) {  
	static int order = 1;
	/* Traverse memory and insert process */
	segment_t *curr, *prev;
	curr = memory->head;
	while(curr) {
		prev = curr;
		curr = curr->next;
		if(prev->status == FREE && prev->size >= process.size) {
			/* Add the process to the memory */
			add_process_to_segment(prev, process, order++);
			/* Combine memory segments */
			memory = combine_free_segments(memory);
			break;
		}
	}
	return memory;
}

/* A function which performs the best fit algorithm.
 * Input: The pointer to memory, and the process to load.
 * Output: A pointer to memory.
 */
memory_t *best_fit(memory_t *memory, process_t process) {
	static int order = 1;
	/* Traverse memory and insert process */
	segment_t *curr, *prev;
	curr = memory->head;
	segment_t *min_segment = NULL;
	int min_size;
	while(curr) {
		prev = curr;
		curr = curr->next;
		if(prev->status == FREE && prev->size >= process.size) {
			if(!min_segment || prev->size < min_size) {
				min_size = prev->size;
				min_segment = prev;
			}
		}
	}
	add_process_to_segment(min_segment, process, order++);
	/* Combine memory segments */
	memory = combine_free_segments(memory);
	return memory;
}

/* A function which performs the worst fit algorithm.
 * Input: The pointer to memory, and the process to load.
 * Output: A pointer to memory.
 */
memory_t *worst_fit(memory_t *memory, process_t process) {
	static int order = 1;
	/* Traverse memory and insert process */
	segment_t *curr, *prev;
	curr = memory->head;
	segment_t *max_segment = NULL;
	int max_size;
	while(curr) {
		prev = curr;
		curr = curr->next;
		if(prev->status == FREE && prev->size >= process.size) {
			if(!max_segment || prev->size > max_size) {
				max_size = prev->size;
				max_segment = prev;
			}
		}
	}
	add_process_to_segment(max_segment, process, order++);
	/* Combine memory segments */
	memory = combine_free_segments(memory);
	return memory;
}

/* A function which performs the next fit algorithm.
 * Input: The pointer to memory, and the process to load.
 * Output: A pointer to memory.
 */
memory_t *next_fit(memory_t *memory, process_t process) {
	static int order = 1;
	static segment_t *curr = NULL, *prev = NULL;
	/* Traverse memory and insert process */
	if(!curr) {
		curr = memory->head;
	}
	while(curr) {
		prev = curr;
		curr = curr->next;
		if(prev->status == FREE && prev->size >= process.size) {
			int remaining_size = prev->size - process.size;
			/* Add the process to the memory */
			add_process_to_segment(prev, process, order++);
			/* If there is any remaining size create a new node */
			if(remaining_size > 0) {
				curr = prev->next;
			}
			/* Combine memory segments */
			memory = combine_free_segments(memory);
			break;
		}
		/* If curr is null restart search from start of memory */
		if(!curr) {
			curr = memory->head;
		}
	}
	return memory;
}

/* A function which adds the process to a memory 
 * segment.
 * Input: Memory segment to add the process to,
 * and the process, the order of the process.
 * Output: None.
 */
void add_process_to_segment(segment_t *segment, process_t process, int order) {
	/* Check if segment is larger than process. */
	int remaining_size = segment->size - process.size;
	/* Add the process to the segment */
	segment->status = RESERVED;
	segment->process = process;
	segment->size = process.size;
	segment->order = order;
	/* If there is any remaining size create a new node */
	if(remaining_size > 0) {
		segment_t *new;
		new = (segment_t *)malloc(sizeof(*new));
		assert(new != NULL);
		new->status = FREE;
		new->start_address = segment->start_address + segment->size;
		new->size = remaining_size;
		new->next = segment->next;
		segment->next = new;
	}
}
/*----------------------------------------------------------------------*/