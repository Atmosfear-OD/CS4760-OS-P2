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
	int sleepT = atoi(argv[0]);
	int repeatF = atoi(argv[1]);
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

	while(i < repeatF) {
		pid_t id = getpid();
		char *msg;
		char *pid;
		sprintf(pid, "%d", id);

		sprintf(msg, pid, " ", i, " of ", repeatF); // Formatted message
		
		// Print to output file using logmsg
		logmsg(msg);

		// Sleep before looping again
		sleep(sleepT);
		
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
