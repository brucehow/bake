/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "targets.h"
#include "variables.h"
#include "append.h"
#include "readfile.h"

void debug() {
	variable *temp = variableList;
	printf("\n================ DEBUG ================\nCURRENT VAR\n");
	while(temp != NULL) {
		printf("%s = %s\n", temp->variable, temp->value);
		if(temp->next == NULL) {
			break;
		}
		temp = temp->next;
	}
	printf("\nCURRENT targetS\n");
	target *tempt = targetList;
	while(tempt != NULL) {
		printf("%s -> ", tempt->target);
		for(int i = 0; i < tempt->numDep; i++) {
			printf("%s ", tempt->dependencies[i]);
		}
		for(int i = 0; i < tempt->numAct; i++) {
			printf("\n%i. %s", i+1, tempt->actions[i]);
		}
		printf("\n");
		tempt = tempt->next;
	}
}

int main(int argc, char *argv[]) {
	// Check filepath validity
	FILE *fp = fopen("bakefile", "r");
	if(fp == NULL) {
		fprintf(stderr, "Could not open bakefile %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while(!feof(fp)) {
		// Reads extended '\' lines
		char *line = readFile(fp);

		// Process the line if valid
		if(line) {
			// Check if it is an action line
			if(currentTarget != NULL && *line == '\t') {
				processActionDef(line);
	        } else { // Process var/target line
	            currentTarget = NULL;
	          	readLine(line);
	        }
		}
	}
	//debug();
	exit(EXIT_SUCCESS);
}
