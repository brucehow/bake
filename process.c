/* CITS2002 Project 2018
 * Names:	Bruce How, Vincent Tian
 * Student numbers: 22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "process.h"
#include "struct.h"


void process(char *ch) {

	bool found = false;
	bool isVariable = false;

	// Variable/target name
	char *key;
	// Value/dependencies
	char *value;

	// Iterate each char in the line
	while(*ch != '\n') {

		if(!found) {
			if(!isspace(*ch)) {
				// Check for alpha-numerical and dot
				if(isalpha(*ch) || isdigit(*ch) || *ch == '.') {
					if(key == NULL) {
						key = malloc(2 * sizeof(char));
						if(key == NULL) {
							perror(__func__);
							exit(EXIT_FAILURE);
						}
						key[0] = *ch;
						key[1] = '\0';
					} else {
						int len = strlen(key);
						key = realloc(key, (len+2) * sizeof(char));
						if(key == NULL) {
							perror(__func__);
							exit(EXIT_FAILURE);
						}
						key[len] = *ch;
						key[len+1] = '\0';
					}
				}
				// Check for variable symbols
				else if(*ch == '=') {
					isVariable = true;
					found = true;
				}
				// Check for target symbols
				else if(*ch == ':') {
					found = true;
				}
			}
		} else {
			if(value == NULL) {
				if(!isspace(*ch)) {
					value = malloc(2 * sizeof(char));
					if(value == NULL) {
						perror(__func__);
						exit(EXIT_FAILURE);
					}
					value[0] = *ch;
					value[1] = '\0';
				}
			} else {
				int len = strlen(value);
				value = realloc(value, (len+2) * sizeof(char));
				if(value == NULL) {
					perror(__func__);
					exit(EXIT_FAILURE);
				}
				value[len] = *ch;
				value[len+1] = '\0';
			}
		}
		ch++;
	}
	if(isVariable) {
		addVariable(key, value);
	} else {
		addTarget(key, value);
	}
	free(key);
	free(value);
}
