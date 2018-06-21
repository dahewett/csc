/*Required Headers*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "rw.h"
#include "resource.h"

/*
 * Declarations for reader-writer shared variables -- plus concurrency-control
 * variables -- must START here.
 */

static resource_t data;

pthread_mutex_t mutex;
pthread_cond_t cond_reader;
pthread_cond_t cond_writter;

int reader_status;
int writer_status;
int 


void initialize_readers_writer() {
    /*
     * Initialize the shared structures, including those used for
     * synchronization.
     */
	 pthread_mutex_init(&mutex, NULL);
	 
	 pthread_cond_init(&cond_reader, NULL);
	 pthread_cond_init(&cond_writter, NULL);
}


void rw_read(char *value, int len) {
    printf("NOTHING IMPLEMENTED YET FOR rw_read\n");
}


void rw_write(char *value, int len) {
    printf("NOTHING IMPLEMENTED YET FOR rw_write\n");
}
