/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "process.h"
#include "variables.h"
#include "targets.h"
#include "append.h"
#include "readfile.h"
#include "bake.h"

#define OPTLIST "C:f:inps"

// Argument flags
bool iflag = false;
bool nflag = false;
bool sflag = false;

void printInfo() {
	// Variables
	variable *varItem = variableList;
	printf("\n\033[1m\033[37mVARIABLES\033[0m\n");
	while(varItem != NULL) {
		printf("\t%s = %s\n", varItem->variable, varItem->value);
		varItem = varItem->next;
	}
	// Targets
	printf("\033[1m\033[37mTARGETS\033[0m\n");
	target *targetItem = targetList;
	while(targetItem != NULL) {
		printf("\t%s : ", targetItem->target);
		for(int i = 0; i < targetItem->numDep; i++) {
			printf("%s ", targetItem->dependencies[i]);
		}
		targetItem = targetItem->next;
		printf("\n");
	}
	// Actions
	printf("\033[1m\033[37mACTIONS\033[0m");
	target *actionItem = targetList;
	while(actionItem != NULL) {
		printf("\n\t%s\n", actionItem->target);
		for(int i = 0; i < actionItem->numAct; i++) {
			printf("\t%i. %s\n", i+1, actionItem->actions[i]);
		}
		actionItem = actionItem->next;
	}
	printf("\n");

}

int main(int argc, char *argv[]) {

	int opt;
	bool pflag = false;
	char *filename = NULL;
	char *dirpath = NULL;
	opterr = 0; // Use our own error printing

	// Argument handler
	while((opt = getopt(argc, argv, OPTLIST)) != -1) {
		switch(opt) {
			case 'i':
				iflag = !iflag;
				break;
			case 'n':
				nflag = !nflag;
				break;
			case 'p':
				pflag = !pflag;
				break;
			case 's':
				sflag = !sflag;
				break;
			case 'C':
				dirpath = strdup(optarg);
				break;
			case 'f':
				filename = strdup(optarg);
				break;
			case '?':
				if(optopt == 'C') {
					fprintf(stderr, "Usage: %s [-C] [dirname]\n", argv[0]);
					exit(EXIT_FAILURE);
				} else if(optopt == 'f') {
					fprintf(stderr, "Usage: %s [-f] [filename]\n", argv[0]);
					exit(EXIT_FAILURE);
				} else {
					fprintf(stderr, "Illegal argument -%c\nUsage: %s [-Cfinps] [file..]\n", optopt, argv[0]);
					exit(EXIT_FAILURE);
				}
		}
	}
	// Check for any targetname options
	char *targetToBuild = NULL;
	argc -= optind;
	argv += optind;
	if(argc > 0) {
		targetToBuild = *argv;
	}

	// Check argument values
	if(dirpath != NULL) {
		int result = chdir(dirpath);
		if(result != 0) {
			fprintf(stderr, "%s: No such directory\n", dirpath);
			exit(EXIT_FAILURE);
		}
	}
	if(filename == NULL) {
		filename = "bakefile";
	}

	FILE *fp = fopen(filename, "r");
	if(fp == NULL) {
		if(dirpath == NULL) {
			perror(filename);
		} else {
			fprintf(stderr, "%s%s: No such file\n", dirpath, filename);
		}
		exit(EXIT_FAILURE);
	}

	// Iterate through the file
	while(!feof(fp)) {
		// Reads extended '\' lines
		char *line = readFile(fp);

		// Process the line if valid
		if(line) {
			if(currentTarget != NULL && *line == '\t') {
				processActionDef(line);
	        } else {
	            currentTarget = NULL;
	          	readLine(line);
	        }
		}
	}
	if(pflag) {
		printInfo();
	} else {
		bake(targetToBuild);
	}
	exit(EXIT_SUCCESS);
}
