/*
 * =====================================================================================
 *
 *       Filename:  lab3p2.c
 *
 *    Description:  Lab 3 part 2 CS2106
 *
 *        Version:  1.0
 *        Created:  03/11/2018 20:49:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//Global variable
int ctr=0;
pthread_t thread[10];

void* child(void* t) {
	printf("I am child %d. Ctr=%d\n", t, ctr);
	ctr++;
	pthread_exit(NULL);
}

int main() {
	int i;

	// Initialize ctr
	ctr=0;

	// Create the threads
	for (i = 0; i < 10; i++) {
		pthread_create(&thread[i], NULL, child, (void *) i);
	}

	for (i = 0; i < 10; i++) {
		pthread_join(thread[i], NULL);
	}
:q






	// And print out ctr
	printf("Value of ctr=%d\n", ctr);
	return 0;
}
