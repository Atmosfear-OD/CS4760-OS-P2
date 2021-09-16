/*
 * testsim.c by Pascal Odijk 9/15/2021
 * P2 CS4760 Prof. Bhatia
 *
 * Descr...
 */

#include <stdio.h>
#include "config.h"

int shmid;
struct nLicenses *shm;

int main(int argc, char* argv[]) {

	signal(SIGINT, signalHandler);
	
	int i = 0;
	int sleep = atoi(argv[0]);
	int repeat = atoi(argv[1]);
	key_t key = 5678;
	
	// Get shared memory id from parent
	if((shmid = shmget(key, sizeof(struct nLicenses) * 2, 0666)) < 0) {
		perror("testsim: Error: shmget ");
		exit(1);
	}

	// Attach shared memory to child
	if((shm = (struct nLicenses *)shmat(shmid, NULL, 0)) == (struct nLicenses *) -1) {
		perror("testsim: Error: shmat ");
		exit(1);
	}

	while(i < repeat) {
		// TODO print to output file using logmsg

		// TODO Sleep
		i++;
	}

	shm->runningProcesses--;
	killProcesses();
	exit(0);
}

void signalHandler() {
	int id = getpid();

	killProcesses();
	killpg(id, SIGINT);
	exit(1);
}

void killProcesses() {
	shmdt(shm);
}
