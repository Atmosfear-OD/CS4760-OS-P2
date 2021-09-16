/*
 * license.c by Pascal Odijk 9/15/2021
 * P2 CS4760 Prof. Bhatia
 *
 * This file is the license obj. It handles all the functions stated in runsim.h.
 */

#include "config.h"

int availableLic;	// Num of licenses available at the time
int block;		// Flag for if all licenses are gone and getlicense() needs to block
FILE *ofptr;		// Output file pointer
int shmid;
struct nLicenses *shm;
key_t key = 5678;

// Initialize object
int initlicense() {
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

	availableLic = shm->num
	printf("number of licenses available: %d\n", availableLic);
	block = 0;

	return availableLic;
}

int getlicense() {
	if(availableLic <= 0) {
		block = 1;  // Block until one becomes available
	}

	return block;
}

// Increment licenses available
int returnlicense() {
	addtolicenses(1);
	return availableLic;
}

// Add n licenses to the number available
void addtolicenses(int n) {
	availableLic += n;
}

// Decrements the number of licenses by n
void removelicenses(int n) {
	availableLic -= n;
}

// Log the messages to output file
void logmsg(char *msg) {
	// Open outfile
	if((ofptr = fopen("logfile.data", "w")) == NULL) {
		perror("runsim: Error: ");
		exit(1);
	}
	
	// Append time
	addTime();
	
	// Print msg to file
	fprintf(ofptr, "%s\n", msg);

	// Close outfile
	fclose(ofptr);
}

// Add current time
void addTime() {
	time_t tm;
	time(&tm);
	struct tm *tp = localtime(&tm);

	fprintf(ofptr, "%.2d:%.2d:%.2d ", tp->tm_hour, tp->tm_min, tp->tm_sec);
}
