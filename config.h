/*
 * config.h by Pascal Odijk 9/15/2021
 * P2 CS4760 Prof. Bhatia
 *
 * Header file for runsim, contains function prototypes for license obj.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>


struct nLicenses {
	int num;
	int runningProcesses;	
};

void signalHandler();
void killProcesses();

int getlicense();
int returnlicense();
int initlicense();
void addtolicenses(int n);
void removelicenses(int n);
void logmsg(const char* msg);

#endif
