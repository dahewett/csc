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

// initialize guards
int guard_reader, guard_writer, guard_active_writer;


// Code adapted from: Csc 360 Sum 18 slides:
// https://connex.csc.uvic.ca/access/content/group/3b0d6b23-22bc-4a1a-892c-cd3e67333ceb/Lectures/02_concurrency_DRAFT.pdf
void initialize_readers_writer() {
    /*
     * Initialize the shared structures, including those used for
     * synchronization.
     */
	int reader_status, writer_status, mutex_status;
	 
	guard_reader = 0;
	guard_writer = 0;
	guard_active_writer = 0;
	
	 // to store return value whichk will be 0 if successful 
	mutex_status = pthread_mutex_init(&mutex, NULL);
	// if 0 error creating mutex
	if (mutex_status != 0) {
		fprintf(stderr, "Mutex: Could not initialize 'mutex'\n");
		exit(1);
	}
	 
	reader_status = pthread_cond_init(&cond_reader, NULL);
	if (reader_status != 0) {
		fprintf(stderr, "Reader: Could not initialize 'reader'\n");
		exit(1);
	}
	
	writer_status = pthread_cond_init(&cond_writter, NULL);
	if (writer_status != 0) {
		fprintf(stderr, "Writer: Could not initialize 'writer'\n");
		exit(1);
	}
}

// waits until free mutex and writter not writing to read the data
void rw_read(char *value, int len) {
	
	// lock the mutex for reading
    pthread_mutex_lock(&mutex);
	
	// while guard writer is true (writer writting) wait.
	while(!(guard_writer) == 0) {
		pthread_cond_wait(&cond_reader, &mutex);
	}
	// set the guard to reading true
	guard_reader++;
	// unlock mutex from writer
	pthread_mutex_unlock(&mutex);
	// reads the data
	read_resource(&data, value, len);
	// locks the mutex to update shared 
	pthread_mutex_lock(&mutex);
	
	// if done reading set reader guard false and signal writer
	if(--guard_reader == 0 ) {
		pthread_cond_signal (&cond_writter);
	}
	// unlock when complete function call
	pthread_mutex_unlock(&mutex);
	
}

// writer- priority
void rw_write(char *value, int len) {
    
	// locks the mutex 
	pthread_mutex_lock(&mutex);
	// 
	guard_writer++;
	
	// wait when 
	while(!((guard_reader == 0) && (guard_active_writer == 0))) {
		pthread_cond_wait(&cond_writter, &mutex);
	}
	// sets the acive writter guard to true
	guard_active_writer++;
	pthread_mutex_unlock(&mutex);
	
	write_resource(&data, value, len);
	
	pthread_mutex_lock(&mutex);
	
	guard_writer--;
	guard_active_writer--;
	
	// when 
	if(guard_writer) {
		// unblock writer
		pthread_cond_signal(&cond_writter);
	} else {
		// unblocks all
		pthread_cond_broadcast(&cond_reader);
	}
	pthread_mutex_unlock(&mutex);
	
}
