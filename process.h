/*************************************************************************
* Name: Rohan Sharma                                                     *
* Login: rsharma1                                                        *
* Student Number: 639271                                                 *
* COMP30023: Computer Systems Project 1: Memory Manager                  *
*                                                                        *
* process.h: This is a header file which defines the data structure      *
* of a process which will be used in the simulation.                     *
*************************************************************************/
#ifndef PROCESS_H
#define PROCESS_H 
/*-------------------------    Data structure  -------------------------*/
/* The structure below represents a process.
 * pid: The processID (a positive integer).
 * size: The size of the process (a positive integer).
 * swapped_out: The amount of times the process has
 * been swapped out of main memory.
 */
typedef struct {
	int pid;
	int size;
	int swapped_out;
} process_t;
#endif
/*----------------------------------------------------------------------*/