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

char *builtTarget = NULL;

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

// Main function handling building of targets
void buildTarget(char *target) {
	bool buildRequired = false;

	// Iterator to iterate through the list
	struct targetNode *it = targetList;

	while(strcmp(it->target, target) != 0) {
		it = it->next;
		if(it == NULL) {
			fprintf(stderr, "%s: No such target found\n", target);
			exit(EXIT_FAILURE);
		}
	}
	time_t targetDate = getFileModDate(it->target);
	time_t dependencyDate;

	// If there are no dependecies, we build it
	if(it->numDep == 0) {
		buildRequired = true;
	}

	for(int i = 0; i < it->numDep; i++) {
		if(isUrl(it->dependencies[i])) {
			dependencyDate = getURLModDate(it->dependencies[i]);
		} else {
			dependencyDate = getFileModDate(it->dependencies[i]);
		}
		if(dependencyDate == 0 || targetDate == 0
			|| difftime(targetDate, dependencyDate) < 0) {
			buildRequired = true;

			// See if the dependency is also a target
			if(!isUrl(it->dependencies[i])) {
				struct targetNode *itTar = targetList;

				while(itTar != NULL) {
					if(strcmp(itTar->target, it->dependencies[i]) == 0) {
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
				// Just print, dont execute
				printf("%s\n", it->actions[i]);
			} else {
				execute(it->actions[i]);
			}
		}
	} else if(strcmp(target, builtTarget) == 0) {
		printf("Bake: '%s' is up to date\n", builtTarget);
		exit(EXIT_SUCCESS);
	}
}

// Pre-checks to determine the "main" target to build
void bake(char *targetToBuild) {
	// Check that there are targets
	if(targetList == NULL) {
		fprintf(stderr, "Could not identify any targets in the specified file\n");
		exit(EXIT_FAILURE);
	}

	// Check if a target name was specified
	if(targetToBuild == NULL) {
		targetToBuild = targetList->target;
	}
	builtTarget = targetToBuild;
	buildTarget(targetToBuild);
}
