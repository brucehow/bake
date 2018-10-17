/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include "process.h"

void read_file(FILE *bakefile) {
	char line[BUFSIZ];

	while(fgets(line, sizeof line, bakefile) != NULL) {
		char *ch = line;
		if(*ch == '#') {
            continue;
        }
        process_line(ch);
        /* Check if this is an action line
        if(ch[0] == '\t' && current_target != NULL) {
            process_action(current_target, ch);
        } else {
            current_target = NULL; // Finished with target's action(s)
		    process_line(ch);
        }*/
	}
}

int main(int argc, char *argv[]) {
	// Check command line arguments
	if (argc < 2) {
		fprintf(stderr, "Expected at least 2 arguments but only 1 was supplied\n");
		exit(EXIT_FAILURE);
	}

	// Check filepath validity
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) {
		fprintf(stderr, "Could not open bakefile %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	read_file(fp);
	exit(EXIT_SUCCESS);
}
