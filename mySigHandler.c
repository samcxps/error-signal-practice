///////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
// Other Files:      N/A
// Semester:         CS 354 Fall 2020
//
// Author:           Samson Cain
// Email:            srcain@wisc.edu
// CS Login:         samson
//
/////////////////////////////////////////////////////////////////////////////// 
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// Global var for seconds between print
int SECONDS = 3;

// Global var for sigusr1 count
int SIGUSR1_COUNT = 0;

/*
 * SIGALRM Handler
 */
void handler_SIGALRM() {
    time_t currTime;
    time(&currTime);

    printf("PID: %i CURRENT TIME: %s", getpid(), ctime(&currTime));

    // Re-arm 3 second alarm
    if (alarm(SECONDS) != 0) {
	    printf("Alarm Error\n");
        exit(1);
	}
}

/*
 * SIGUSR1 Handler
 */
void handler_SIGUSR1() {
    printf("SIGUSR1 handled and counted!\n");
    SIGUSR1_COUNT++;
}

/*
 * SIGINT Handler
 */
void handler_SIGINT() {
    printf("\n");
    printf("SIGINT handled.\n");
    printf("SIGUSR1 was handled %i times. Exiting now.\n", SIGUSR1_COUNT);
    exit(0);
}

int main(int argc, char* argv[]) { 

    // Setup 3 second alarm
    if (alarm(SECONDS) != 0) {
	    printf("Alarm Error\n");
        exit(1);
	}

    // Setup SIGALRM handler
    struct sigaction sigalrm_struct;
    memset(&sigalrm_struct, 0, sizeof(sigalrm_struct));
    sigalrm_struct.sa_handler = handler_SIGALRM;
    if (sigaction(SIGALRM, &sigalrm_struct, NULL) != 0) {
        printf("Error setting up SIGALRM handler\n");
        exit(1);
    }

    // Setup SIGUSR1 handler
    struct sigaction sigusr1_struct;
    memset(&sigusr1_struct, 0, sizeof(sigusr1_struct));
    sigusr1_struct.sa_handler = handler_SIGUSR1;
    if (sigaction(SIGUSR1, &sigusr1_struct, NULL) != 0) {
        printf("Error setting up SIGUSR1 handler\n");
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

    printf("Pid and time print every %i seconds.\n", SECONDS);
	printf("Enter Ctrl-C to end the program.\n");

    while (1) {}
}