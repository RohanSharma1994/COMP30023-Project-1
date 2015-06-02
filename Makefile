# Makefile: Project 1 Computer Systems
# Author: Rohan Sharma, rsharma1
# S.N: 639271
# Memory has no dependencies.
# Main program depends on memory, ready queue and fit algorithms
memswap: fit_algorithms.o ready_queue.o memory.o
	gcc -Wall -o memswap memswap.c fit_algorithms.o ready_queue.o memory.o -lm
memory.o: 
	gcc -Wall -c memory.c 
# Ready queue has no dependencies.
ready_queue.o:
	gcc -Wall -c ready_queue.c 
# Fit algorithms depend on memory
fit_algorithms.o: memory.o
	gcc -Wall -c fit_algorithms.c 
