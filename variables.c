/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "variables.h"
#include "append.h"

variable *variableList = NULL;
variable *lastVariable = NULL;

/**
 * Reads the line after the '=' symbol of a variable declaration and add the
 * appropiate value to the appropiate variable
 */
void processVariableDef(char *word, char *valLine) {
    // Store variable definition in a new structure
    variable *new = calloc(1, sizeof(variable));
    if(new == NULL) {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
    new->variable = strdup(word);

    // Build the value
    char *value = NULL;
    while(isspace(*valLine)) {
        valLine++;
    }
    while(*valLine != '\0') {
        value = append(value, *valLine);
        valLine++;
    }
    // Store the value
    new->value = strdup(value);
    free(value);

    // Add the variable to the list
    if(variableList == NULL) {
        variableList = new;
        lastVariable = new;
    } else {
        lastVariable->next = new;
        lastVariable = new;
    }
}
