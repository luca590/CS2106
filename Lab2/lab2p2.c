/*
 * =====================================================================================
 *
 *       Filename:  lab2p2.c
 *
 *    Description: Question 4 Lab 2
 *
 *        Version:  1.0
 *        Created:  02/25/2018 21:39:24
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
#include <unistd.h>
#include <string.h>

//Maximize size of our comms buffer
#define MAX_BUFFER_LEN		1024

//We will use a pipe to send data form one process to another
int main() {
	int fd[2];

	pipe(fd);

	//Our buffer
	char buffer[1024];

	//# of characters written/read
	int n;

	if(fork() == 0) {		//Child reads from the pipe input
		//Child should close the output side of the pipe
		close(fd[1]);

		//Read from the pipe
		n = read(fd[0], buffer, MAX_BUFFER_LEN);
		printf("Child read %d bytes from parent: %s\n", n, buffer);
		close(fd[0]);
	} else {		//Parent writes to the output of pipe
		int status;
		//Parent should close input side of the pipe
		close(fd[0]);

		//Write to the pipe
		sprintf(buffer, "Hello child! This is your parent!");
		n = write(fd[1], buffer, strlen(buffer) + 1);
		printf("Parent wrote %d byets to the child: %s\n", n, buffer);
		close(fd[1]);

		//Wait for the child ot end
		wait(&status);
	}




