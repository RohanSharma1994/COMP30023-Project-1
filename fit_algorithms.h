/*************************************************************************
* Name: Rohan Sharma                                                     *
* Login: rsharma1                                                        *
* Student Number: 639271                                                 *
* COMP30023: Computer Systems Project 1: Memory Manager                  *
*                                                                        *
* fit_algorithms.h: The header file which includes the functional        *
* prototypes required by the different fit algorihms.                    *
*************************************************************************/

/*-------------------------    Libraries       -------------------------*/
#include "process.h"
#include "memory.h"
#include "ready_queue.h"
/*----------------------------------------------------------------------*/

/*------------------------- Functional prototypes ----------------------*/
/* A function which performs the first fit algorithm.
 * Input: The pointer to memory, and the process to load.
 * Output: A pointer to memory.
 */
memory_t *first_fit(memory_t *, process_t);

/* A function which performs the best fit algorithm.
 * Input: The pointer to memory, and the process to load.
 * Output: A pointer to memory.
 */
memory_t *best_fit(memory_t *, process_t);

/* A function which performs the worst fit algorithm.
 * Input: The pointer to memory, and the process to load.
 * Output: A pointer to memory.
 */
memory_t *worst_fit(memory_t *, process_t);

/* A function which performs the next fit algorithm.
 * Input: The pointer to memory, and the process to load,
 * Output: A pointer to memory.
 */
memory_t *next_fit(memory_t *, process_t);

/* A function which adds the process to a memory 
 * segment.
 * Input: Memory segment to add the process to,
 * and the process, the order of the process.
 * Output: None.
 */
void add_process_to_segment(segment_t *, process_t, int);
/*----------------------------------------------------------------------*/