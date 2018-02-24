/*
 * =====================================================================================
 *
 *       Filename:  lab2p0.c
 *
 *    Description:  Into file for Lab 2 for OS
 *
 *        Version:  1.0
 *        Created:  02/25/2018 07:03:51
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

int main() {
	int cpid;
	if((cpid = fork()) != 0) {
		//Tjis is the parent
		printf("Hello, I am the PARENT. My PID is %d, my child's PID is %d,
			   	and my parent's PID is %d\n", getpid(), cpid, getppid();
	}
	else {
		printf("Hello, I am the CHILD. My PID is %d, my parent's PID is %d, for returned %d.\n",
				getpid(), getppid(), cpid);
	}
}

