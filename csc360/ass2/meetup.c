/*Required Headers*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "meetup.h"
#include "resource.h"

/*
 * Declarations for barrier shared variables -- plus concurrency-control
 * variables -- must START here.
 */
 // resource struct
resource_t resource;
int count;
// how many in the group
int number_t;
// first one or last one has codeword
int who_cw;
// init semaphores
sem_t mutex;
sem_t barrier;
 
void initialize_meetup(int n, int mf) {
    char label[100];
    int i;
    if (n < 1) {
        fprintf(stderr, "Who are you kidding?\n");
        fprintf(stderr, "A meetup size of %d??\n", n);
        exit(1);
    }

    /*
     * Initialize the shared structures, including those used for
     * synchronization.
     */
	 
	// update global vars
	number_t = n;
	who_cw = mf;
	count = 0;
	 
	// initialize resource call  
	init_resource(&resource, "codeword resource");
	
	if (sem_init(&mutex, 0, 1) != 0) {
    	fprintf(stderr, "Semaphore: Failed to initialize semaphore 'mutex'\n");
    	exit(1);
    }
    if (sem_init(&barrier, 0, number_t) != 0) {
    	fprintf(stderr, "Semaphore: Failed to initialize semaphore 'barrier'\n");
    	exit(1);
    }
}


void join_meetup(char *value, int len) {
    
	printf("n = %d, and mf = %d\n", number_t, who_cw);
	sem_wait(&mutex);
	
	if ((who_cw == 1) && (count == 0)){
		write_resource (&resource, value, len);
	} else if (who_cw == 0){
	}
	
	count++;
	if (count == number_t) {
		sem_post(&mutex);
	}
	
	sem_wait(&barrier);
	sem_post(&barrier);
}
