/*
 * runsim.c by Pascal Odijk 9/14/2021
 * P2 CMPSCI 4760 Prof. Bhatia
 *
 * This program takes in the command line arg and checks if it is of valid type and value. Shared memory is then allocated with the number of licenses stated by user arg.
 * The invocation method is:
 * 	./runsim n < testing.data -- where n is an integer number of licenses
 */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "config.h"

#define BUFFERSIZE 100

// Shared memory globals
int shmid;
struct nLicenses *shm;

int main(int argc, char *argv[]) {

	int n;
	signal(SIGINT, signalHandler);

	if(argc > 2) {	// Check for too many args
		printf("runsim: Error: Too many arguments\n");
		printf("Usage: ./runsim n < testing.data -- where n is an integer between 1 & 20\n");

		return 0;
	} else if(argc == 1) {	// Check for no arg
		printf("runsim: Error: No argument given\n");
		printf("Usage: ./runsim n < testing.data -- where n is an integer between 1 & 20\n");

		return 0;
	}	
	
	if(strspn(argv[1], "0123456789") == strlen(argv[1])) {  // Check is n is a number
		n = atoi(argv[1]);
		if(n > 20 || n <= 0) {
			printf("runsim: Error: Integer must be between 1 and 20\n");
			printf("Usage: ./runsim n < testing.data -- where n is an integer 1 & 20\n");

			return 0;
		}
	} else {
		printf("runsim: Error: Invalid argument: %s\n", argv[1]);
		printf("Usage: ./runsim n < testing.data -- where n is an integer between 1 & 20\n");

		return 0;
	}

	// Implement shared memory
	key_t key = 5678;
	
	// Create shared memory id
	if((shmid = shmget(key, sizeof(struct nLicenses) * 2, IPC_CREAT | 0666)) < 0) {
		perror("runsim: Error: shmget ");
		exit(1);
	}

	// Attach shared memory
	if((shm = (struct nLicenses *)shmat(shmid, NULL, 0)) == (struct nLicenses *) -1) {
		perror("runsim: Error: shmat ");
		exit(1);
	}

	// Save data to shared memory
	shm->num = n;
	shm->runningProcesses = 0;

	// Get strings from stdin/file redirection
	char buffer[BUFFERSIZE];
	fgets(buffer, BUFFERSIZE, stdin);
	int i = 0, j = 0;
	char progName[50] = "./";
	char a2[50], a3[50];
	int sleep, repeat;
	
	// Get program name from buffer
	for(i ; buffer[i] != ' ' ; i++) {
		progName[i + 2] = buffer[i];
	}

	i++;
	// Get sleep time
	for(i ; buffer[i] != ' ' ; i++) {
		a2[j] = buffer[i];
		j++;
	}
	
	j = 0;
	i++;
	// Get repeat factor
	for(i ; i < strlen(buffer)-1 ; i++) {
		a3[j] = buffer[i];
		j++;
	}

	//sleep = atoi(a2);
	//repeat = atoi(a3);

	// might delete --
	printf("about to call fork\n");		
	int pid = fork();
	if(pid == 0) {
		//execl(PATH, argv[0], argv[1]);
		printf("about to call execl\n");
		shm->runningProcesses++;
		execl(progName, a2, a3, (char *)NULL);
	}
	printf("back from execl\n");
	killProcesses();
	// --	
	
	return 0;
}

void signalHandler() {
	int id = getpgrp();
	killProcesses();
	killpg(id, SIGINT);
	exit(1);
}

void killProcesses() {
	shmctl(shmid, IPC_RMID, NULL);
	shmdt(shm);
}
