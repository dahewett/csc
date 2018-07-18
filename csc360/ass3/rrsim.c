/*
	Csc 360 Assignment 3- Task 1
	Devin Hewett V00821219
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define MAX_BUFFER_LEN 80

taskval_t *event_list = NULL;
float wait_time;
float turn_arround;
float total_task = 1000.00;
float complete_task = 0;
void print_task(taskval_t *t, void *arg) {
    printf("task %03d: %5d %3.2f %3.2f\n",
        t->id,
        t->arrival_time,
        t->cpu_request,
        t->cpu_used
    );  
}


void increment_count(taskval_t *t, void *arg) {
    int *ip;
    ip = (int *)arg;
    (*ip)++;
}


void run_simulation(int qlen, int dlen) {
	
    taskval_t *ready_q = NULL;
	taskval_t *to_come = NULL;
	taskval_t *current = NULL;
	
	// for cpu ticks
	int cpu_ticks = 0;
	//number of total events
	int num_events = 0;
	taskval_t *temp;
	temp = event_list;
	while(temp != NULL){
		num_events++;
		if ( temp->next != NULL){
			temp = temp->next;
			
		} else {
			temp = NULL;
		}
	}
	int current_event_num = 0;
	// status
	int status = 1;
	int first = 1;
	while(status){
		//CHANGE
		//current_event_num++;
		
		to_come = peek_front(event_list);
		
		
		if(to_come != NULL) {
			// not all task complete therfore idle
			while (current_event_num < num_events && ready_q == NULL){
				if (to_come->arrival_time <= cpu_ticks){
					break;
				}
				printf("[%05d] IDLE\n", cpu_ticks);
				cpu_ticks++;
			}
			// check arrival_time or first time to add to ready queue
			if(first == 1 || to_come->arrival_time <= cpu_ticks) {
				temp = new_task();
				temp->id = to_come->id;
				temp->arrival_time = to_come->arrival_time;
				temp->cpu_request = to_come->cpu_request;
				temp->cpu_used = 0;
				temp->next = to_come->next;
			
				// add to ready queue
				ready_q = add_end(ready_q, temp);
				// remove from event list
				event_list = remove_front(event_list);
				// no longer first event
				first = 0;
			}
		}
		current = peek_front(ready_q);
				
		int cur_arrival_time = current->arrival_time;
		// cpu idle
		while(cpu_ticks < cur_arrival_time){
			printf("[%05d] IDLE\n", cpu_ticks);
			cpu_ticks++;
		}
		
		// when ready for dispatch
		if(cpu_ticks >= cur_arrival_time){
			// dispatch
			int i = 0;
			for(i = 0; i < dlen; i++){
				printf("[%05d] DISPATCHING\n", cpu_ticks);
				cpu_ticks++;
			}
			// amount of cpu required left
			float cpu_left = current->cpu_request - current->cpu_used;
			// length of dispatch for this cycle
			float xlen;
			if (cpu_left < qlen) {
				xlen = cpu_left;
			} else{
				xlen = (float)qlen;
			}
			// do cycle dispatch
			
			for(i = 0; i < xlen; i++){
				printf("[%05d] ", cpu_ticks);
				printf("id=%05d ", current->id);
				printf("req=%.2f ", current->cpu_request);
				printf("used=%.2f\n", current->cpu_used);
				cpu_ticks++;
				current->cpu_used++;
			}
		}
		//check if arrival of new event occured
		to_come =peek_front(event_list);
		
		if(to_come != NULL) {
			// check arrival_time or first time to add to ready queue
			if(to_come->arrival_time <= cpu_ticks) {
				temp = new_task();
				temp->id = to_come->id;
				temp->arrival_time = to_come->arrival_time;
				temp->cpu_request = to_come->cpu_request;
				temp->cpu_used = 0;
				temp->next = to_come->next;
			
				// add to ready queue
				ready_q = add_end(ready_q, temp);
				// remove from event list
				event_list = remove_front(event_list);
			}
		}
		
		// check if event complete
		if (current->cpu_used >= current->cpu_request) {
			float ta = cpu_ticks - current->arrival_time;
			float w = cpu_ticks - current->cpu_request - current->arrival_time;
			printf("[%05d] ", cpu_ticks);
			printf("id=%05d ", current->id);
			printf("EXIT w=%.2f ta=%.2f\n", w, ta);
			current_event_num++;
			ready_q = remove_front(ready_q);
			wait_time = wait_time + w;
			turn_arround = turn_arround + ta;
			complete_task++;
			if (complete_task == total_task){
				FILE *fp;
				fp = fopen("results.txt", "a");
				fprintf(fp,"%d,%d,%f,%f\n", qlen, dlen, wait_time, turn_arround);
			}
		}
		// add to back to ready queue if not complete
		else{
			ready_q = remove_front(ready_q);
			ready_q = add_end(ready_q, current);
		}
		// no more events end while loop
		if(current_event_num >= num_events){
			status = 0;
		}
	}
}


int main(int argc, char *argv[]) {
    char   input_line[MAX_BUFFER_LEN];
    int    i;
    int    task_num;
    int    task_arrival;
    float  task_cpu;
    int    quantum_length = -1;
    int    dispatch_length = -1;

    taskval_t *temp_task;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--quantum") == 0 && i+1 < argc) {
            quantum_length = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "--dispatch") == 0 && i+1 < argc) {
            dispatch_length = atoi(argv[i+1]);
        }
    }

    if (quantum_length == -1 || dispatch_length == -1) {
        fprintf(stderr, 
            "usage: %s --quantum <num> --dispatch <num>\n",
            argv[0]);
        exit(1);
    }


    while(fgets(input_line, MAX_BUFFER_LEN, stdin)) {
        sscanf(input_line, "%d %d %f", &task_num, &task_arrival,
            &task_cpu);
        temp_task = new_task();
        temp_task->id = task_num;
        temp_task->arrival_time = task_arrival;
        temp_task->cpu_request = task_cpu;
        temp_task->cpu_used = 0.0;
        event_list = add_end(event_list, temp_task);
    }

#ifdef DEBUG
    int num_events;
    apply(event_list, increment_count, &num_events);
    printf("DEBUG: # of events read into list -- %d\n", num_events);
    printf("DEBUG: value of quantum length -- %d\n", quantum_length);
    printf("DEBUG: value of dispatch length -- %d\n", dispatch_length);
#endif

    run_simulation(quantum_length, dispatch_length);

    return (0);
}
