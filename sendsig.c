///////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      N/A
// Semester:         CS 354 Fall 2020
//
// Author:           Samson Cain
// Email:            srcain@wisc.edu
// CS Login:         samson
//
/////////////////////////////////////////////////////////////////////////////// 
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, const char *argv[]) {

    if (argc != 3) {
        printf("Usage: <signal type> <pid>\n");
        exit(0);
    }

    char sigType[2];
    strcpy(sigType, argv[1]);

    int pid = atoi(argv[2]);
    
    if (strcmp("-u", sigType) == 0) { // SIGUSR1
        kill(pid, SIGUSR1);
    } else if (strcmp("-i", sigType) == 0) { // SIGINT
        kill(pid, SIGINT);
    } 

	
	return 0;
}