/*************************************************************************
* Name: Rohan Sharma                                                     *
* Login: rsharma1                                                        *
* Student Number: 639271                                                 *
* COMP30023: Computer Systems Project 1: Memory Manager                  *
*                                                                        *
* memswap.c: The main file of the project. It takes in input from stdin, *
* reads in processes from file and deploys appropriate algorithm.        *
*************************************************************************/

/*-------------------------    Libraries       -------------------------*/
#include "memswap.h"
/*----------------------------------------------------------------------*/


/*--------------------  Functional definitions -------------------------*/
/* Handles input, initializes queue and
 * memory and deploys appropriate algorithm.
 */
int main(int argc, char *argv[]) {
	char input, *filename, *algorithm;  
	int size = 0;	
	filename = algorithm = NULL;		
	
	/* Processing the input */
	while ((input = getopt(argc, argv, "f:a:m:")) != EOF)
	{
		if(input == 'f') {
			filename = optarg;
		} else if(input == 'a') {
			algorithm = optarg;
		} else if(input == 'm') {
			size = atoi(optarg);
		} else {
			print_usage();
		}
	}
	if(!filename || !algorithm || !size) {
		print_usage();
	}

	/* Read from the file and populate the ready queue */
	ready_queue_t *queue = process_file(filename);
	/* Create the memory */
	memory_t *memory = make_memory(size);
	
	/* Run the algorithm until the ready queue is empty */
	while(!is_empty(queue)) {
		process_t process = dequeue_process(&queue);
		/* Remove processes from memory until there
		 * is enough continous space to fit process.
		 */
		while(!check_memory(memory, process.size)) {
			process_t dequeued_process = remove_process(&memory);
			queue = queue_process(queue, dequeued_process);
			memory = combine_free_segments(memory);
		}
		
		/* Load a process into memory using one of the algorithms */
		if(strcmp(algorithm, FIRST_FIT) == 0) {
			memory = first_fit(memory, process);
		}
		else if(strcmp(algorithm, BEST_FIT) == 0) {
			memory = best_fit(memory, process);
		}
		else if(strcmp(algorithm, WORST_FIT) == 0) {
			memory = worst_fit(memory, process);
		}
		else if(strcmp(algorithm, NEXT_FIT) == 0) {
			memory = next_fit(memory, process);
		} else {
			print_usage();
		}
		printf("%d loaded, ", process.pid);
		output(memory, size);
	}
	free_memory(memory);
	free_ready_queue(queue);
	return 0;
}

/* A function which reads in a file and returns
 * pointer to a ready queue with all the processes.
 * Input: File name.
 * Output: A pointer to the ready queue filled with
 * processes.
 */
ready_queue_t *process_file(char *filename) {
	/* Open the file */
	FILE *fp;
	fp = fopen(filename, "r");
	assert(fp != NULL);

	/* Create a new ready queue */
	ready_queue_t *queue = make_ready_queue();
	int pid, size;
	process_t process;

	/* Process the file and fill ready queue */
	while(fscanf(fp, "%d %d", &pid, &size) != EOF) {
		process.pid = pid;
		process.size = size;
		process.swapped_out = 0;
		queue = queue_process(queue, process);
	}
	fclose(fp);

	return queue;
}

/* A function which prints the summary of memory
 * after a process has been loaded in it.
 * Input: Pointer to memory, size of memory.
 * Output: None.
 */
void output(memory_t *memory, int msize) {
	/* Get a summary of the memory */
	memory_summary_t summary = memory_summary(memory);
	double mem_usage = (double)summary.reserved_memory/msize*100;
	mem_usage = ceil(mem_usage);
	printf("numprocesses=%d, ", summary.processes);
	printf("numholes=%d, ", summary.holes);
	printf("memusage=%.0f%%\n", mem_usage);
}

/* Prints the usage statement of the program.
 * Input: None.
 * Output: None.
 */
void print_usage() {
	printf("Usage: mem_swap -f filename ");
	printf("-m memory_size ");
	printf("-a {first,best,worst,next}\n");
	exit(EXIT_FAILURE);
}
/*----------------------------------------------------------------------*/