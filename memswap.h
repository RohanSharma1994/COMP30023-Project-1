/*************************************************************************
* Name: Rohan Sharma                                                     *
* Login: rsharma1                                                        *
* Student Number: 639271                                                 *
* COMP30023: Computer Systems Project 1: Memory Manager                  *
*                                                                        *
* memswap.h: Has all the libraries, constants and definitions for        *
* memswap.c                                                              *
*************************************************************************/

/*-------------------------    Libraries       -------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>   
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "fit_algorithms.h"
/*----------------------------------------------------------------------*/

/*-------------------------    Constants       -------------------------*/
#define FIRST_FIT "first"
#define BEST_FIT "best"
#define WORST_FIT "worst"
#define NEXT_FIT "next"
/*----------------------------------------------------------------------*/

/*-------------------------    Data structure  -------------------------*/
/* External declarations */
extern  int     optind;
extern  char    *optarg;
/*----------------------------------------------------------------------*/

/*--------------------  Functional prototypes  -------------------------*/
/* A function which prints the summary of memory
 * after a process has been loaded in it.
 * Input: Pointer to memory, size of memory.
 * Output: None.
 */
void output(memory_t*, int);

/* A function which reads in a file and returns
 * pointer to a ready queue with all the processes.
 * Input: File name.
 * Output: A pointer to the ready queue filled with
 * processes.
 */
ready_queue_t *process_file(char *);

/* Prints the usage statement of the program.
 * Input: None.
 * Output: None.
 */
void print_usage();
/*----------------------------------------------------------------------*/