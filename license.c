/*
 * license.c by Pascal Odijk 9/15/2021
 * P2 CS4760 Prof. Bhatia
 *
 * This file is the license obj. It handles all the functions stated in runsim.h.
 */

#include "runsim.h"

int availableLic;	// Num of licenses available at the time
int block;		// Flag for if all licenses are gone and getlicense() needs to block

// Initialize object
int initlicense() {
	printf("number of licenses available: %d\n", runsim->nLicense);
	//addtolicenses(runsim->nLicense);
	block = 0;
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
