/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "struct.h"

VARIABLE *variables = NULL;
VARIABLE *lastVariable = NULL;

TARGET *targets = NULL;
TARGET *lastTarget = NULL;

void addVariable(char *var, char *value) {
	VARIABLE *new = malloc(sizeof(VARIABLE));

	if(new == NULL) {
		perror(__func__);
		exit(EXIT_FAILURE);
	}

	new->var = strdup(var);
	new->value = strdup(value);
	new->next = NULL;

	// Keep track of the last variable
	if(lastVariable == NULL) {
		lastVariable = new;
		variables = new;
	} else {
		lastVariable->next = new;
		lastVariable = new;
	}
}

void addTarget(char *target, char *value) {
	TARGET *new = malloc(sizeof(TARGET));

	if(new == NULL) {
		perror(__func__);
		exit(EXIT_FAILURE);
	}

	new->target = strdup(target);
	new->next = NULL;

	char *dependency;
	int count = 0;

	// Extract each dependency from the value
	while(*value != '\0') {
		// Exclude spaces before the dependencies
		if(new->dependencies == NULL && isspace(*value)) {
			value++;
			continue;
		}
		// Build the dependency
		if(isalpha(*value) || isdigit(*value) || *value == '.') {
			if(dependency == NULL) {
				dependency = malloc(2 * sizeof(char));
				if(dependency == NULL) {
					perror(__func__);
					exit(EXIT_FAILURE);
				}
				dependency[0] = *value;
				dependency[1] = '\0';
			} else {
				int len = strlen(dependency);
				dependency = realloc(dependency, (len+2) * sizeof(char));
				if(dependency == NULL) {
					perror(__func__);
					exit(EXIT_FAILURE);
				}
				dependency[len] = *value;
				dependency[len+1] = '\0';
			}
		} // End of a single dependency
		else if(isspace(*value)) {
			if(count == 0) {
				new->dependencies = malloc(sizeof(char *));
				new->dependencies[0] = strdup(dependency);
				count++;
				free(dependency);
			} else {
				count++;
				new->dependencies = realloc(new->dependencies, count * sizeof(char *));
				new->dependencies[count] = strdup(dependency);
				free(dependency);
			}
		}
		value++;
	}

	// Keep track of the last target
	if(lastTarget == NULL) {
		lastTarget = new;
		targets = new;
	} else {
		lastTarget->next = new;
		lastTarget = new;
	}
}


// PRINTING FOR TESTS
void debug() {
	VARIABLE *var = variables;

	printf("\nVariables\n");
	while(var != NULL) {
		printf("%s = %s\n", var->var, var->value);
		var = var->next;
	}
}
