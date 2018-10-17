/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"
#include "process.h"

void read(FILE *bakefile) {
	char line[BUFSIZ];
	
	while(fgets(line, sizeof line, bakefile) != NULL) {
		char *ch = line;
		if(ch[0] != '#' && ch[0] != '\t') {
			process(ch);
		}
	}
	debug();
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
		fprintf(stderr, "Could not open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	read(fp);
	exit(EXIT_SUCCESS);
}
