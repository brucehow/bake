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

void bake_file(char *file) {

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
		char *line = read_file(fp);

		// Process the line if valid
		if(line) {
			// Check if it is an action line
			if(current_target != NULL && *line == '\t') {
				printf("ACTION: %s\n", line); // DEBUG PRINT
				process_action_def(line);
	        } else { // Process var/target line
				printf("DECLARATION: %s\n", line); // DEBUG PRINT
	            current_target = NULL;
	          	process_line(line);
	        }
		}
	}
	//bake_file();
	exit(EXIT_SUCCESS);
}
