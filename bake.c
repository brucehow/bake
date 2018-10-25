/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "bake.h"
#include "main.h"
#include "targets.h"
#include "filedate.h"
#include "curl.h"

// Stores the original target to build
char *targetToBuild = NULL;

/**
 * Uses fork() to create child processes to execute bash commands. Checks for
 * exit statuses, the iflag and action line modifiers to alter the output
 */
void execute(char *command) {
	bool silenced = sflag;
	switch(fork()) {
		case -1: // Process creation failed
			perror("Fork");
			exit(EXIT_FAILURE);
		case 0: // Child process
			if(*command == '@') {
				silenced = true;
				command++;
			}
			if(!silenced) {
				printf("%s\n", command);
			}
			execl("/bin/sh", "sh", "-c", command, NULL);
			perror("execl");
			break;
		default: {
			int status;
			wait(&status);
			if(WEXITSTATUS(status) != 0 && !iflag && *command != '-') {
				printf("Bake: Unsucessful execution at\n\t'%s'\n", command);
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * Handles the building of a target. Uses the targetList LinkedList to identify * a particular target's dependencies. The function is recusive and calls
 * itself when a dependency is also a target that may require building.
 */
void buildTarget(char *target) {
	bool buildRequired = false;

	// Iterator to iterate through the target list
	struct targetNode *it = targetList;

	// Find the target that matches 'target'
	while(strcmp(it->target, target) != 0) {
		it = it->next;
		if(it == NULL) {
			fprintf(stderr, "%s: No such target found\n", target);
			exit(EXIT_FAILURE);
		}
	}
	// Date 0 is returned if the file is non-existant
	time_t targetDate = getFileModDate(it->target);
	time_t dependencyDate;

	// If there are no dependecies or target doesnt exits as a file
	if(it->numDep == 0 || targetDate == 0) {
		buildRequired = true;
	}

	for(int i = 0; i < it->numDep; i++) {
		if(isUrl(it->dependencies[i])) {
			dependencyDate = getURLModDate(it->dependencies[i]);
		} else {
			dependencyDate = getFileModDate(it->dependencies[i]);
		}
		if(difftime(targetDate, dependencyDate) <= 0) {
			buildRequired = true;

			// See if the dependency is also a target
			if(!isUrl(it->dependencies[i])) {
				struct targetNode *itTar = targetList;

				while(itTar != NULL) {
					if(strcmp(itTar->target, it->dependencies[i]) == 0) {
						// Recursively build the target and it's dependecies
						buildTarget(it->dependencies[i]);
					}
					itTar = itTar->next;
				}
			}
		}
	}
	if(buildRequired) {
		for(int i = 0; i < it->numAct; i++) {
			if(nflag) {
				// Just print, dont execute the commands
				printf("%s\n", it->actions[i]);
			} else {
				execute(it->actions[i]);
			}
		}
	}
	// No building required and we are trying to build targetToBuild
	else if(strcmp(target, targetToBuild) == 0) {
		printf("Bake: '%s' is up to date\n", targetToBuild);
		exit(EXIT_SUCCESS);
	}
}

/**
 * Determines the initial target to build. Identifies if the initial target to
 * be built is specified in as an argument or is the first target in the
 * Bakefile
 */
void bake(char *targetArg) {
	// Check that there are targets
	if(targetList == NULL) {
		fprintf(stderr, "Could not identify any targets in the specified file\n");
		exit(EXIT_FAILURE);
	}

	// Check if a target arg was specified
	if(targetArg == NULL) {
		targetToBuild = targetList->target;
	} else {
		targetToBuild = targetArg;
	}
	buildTarget(targetToBuild);
}
