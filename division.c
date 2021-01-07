///////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
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

#define BUFF_SIZE 100

// Global var for success count
int SUCCESS_COUNT = 0;

/*
 * SIGFPE Handler
 */
void handler_SIGFPE() {
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %i\n", SUCCESS_COUNT);
    printf("The program will be terminated.\n");
    exit(0);
}

/*
 * SIGINT Handler
 */
void handler_SIGINT() {
    printf("\n");
    printf("Total number of operations completed successfully: %i\n", SUCCESS_COUNT);
    printf("The program will be terminated.\n");
    exit(0);
}

int main (int argc, const char *argv[]) {

    // Local vars
    char buffer[BUFF_SIZE];
    int n1, n2;
    int q, r;

    // Setup SIGALRM handler
    struct sigaction sigfpe_struct;
    memset(&sigfpe_struct, 0, sizeof(sigfpe_struct));
    sigfpe_struct.sa_handler = handler_SIGFPE;
    if (sigaction(SIGFPE, &sigfpe_struct, NULL) != 0) {
        printf("Error setting up SIGALRM handler\n");
        exit(1);
    }

    // Setup SIGINT handler
    struct sigaction sigint_struct;
    memset(&sigint_struct, 0, sizeof(sigint_struct));
    sigint_struct.sa_handler = handler_SIGINT;
    if (sigaction(SIGINT, &sigint_struct, NULL) != 0) {
        printf("Error setting up SIGINT handler\n");
        exit(1);
    }

    while (1) {
        // Get first int from stdin
		printf("Enter first integer: ");
		if (fgets(buffer, BUFF_SIZE, stdin) != NULL) {
			n1 = atoi(buffer);
		}

        // Get second int from stdin
		printf("Enter second integer: ");
		if (fgets(buffer, BUFF_SIZE, stdin) != NULL) {
			n2 = atoi(buffer);
		}
		
        // Calculate quotient and remainder
		q = n1 / n2;		
		r = n1 % n2;
		
        // Print and increment success
		printf("%d / %d is %d with a remainder of %d\n", n1, n2, q, r);
		SUCCESS_COUNT++;
	}

	return 0;
}