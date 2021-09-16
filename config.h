/*
 * config.h by Pascal Odijk 9/15/2021
 * P2 CS4760 Prof. Bhatia
 *
 * Header file for runsim and testsim -- contains function prototypes for license obj.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>


struct nLicenses {
	int num;
	int runningProcesses;	
};

time_t addTime();
void signalHandler();
void killProcesses();

extern int getlicense();
extern int returnlicense();
extern int initlicense();
extern void addtolicenses(int n);
extern void removelicenses(int n);
extern void logmsg(char* msg);

#endif
