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

VARIABLE *variables = NULL;
TARGET *targets = NULL;

void addVariable(char *var, char *value) {
	VARIABLE *new = malloc(sizeof(VARIABLE));

	if(new == NULL) {
		perror(__func__);
		exit(EXIT_FAILURE);
	}

	new->key = strdup(var);
	new->value = strdup(value);
	new->next = variables;
	variables = new;
}

void addTarget(char *var, char* value) {
	TARGET *new = malloc(sizeof(TARGET));

	if(new == NULL) {
		perror(__func__);
		exit(EXIT_FAILURE);
	}

	new->target = strdup(var);
	new->dependencies = strdup(value);
	new->next = targets;
	targets = new;
}

// PRINTING FOR TESTS
void debug() {
	VARIABLE *var = variables;

	printf("=============\nVariables\n");
	while(var != NULL) {
		printf("%s = %s\n", var->key, var->value);
		var = var->next;
	}

	TARGET *tar = targets;
	printf("\n\nTargets\n");
	while(tar != NULL) {
		printf("%s : %s\n", tar->target, tar->dependencies);
		tar = tar->next;
	}
	printf("=============\n");

}
