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

void processVariableDef(char *word, char *ch) {
    // Store variable definition in a new structure
    variable *new = malloc(sizeof(variable));
    if(new == NULL) {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
    new->variable = strdup(word);

    // Build the value
    char *value = NULL;
    while(isspace(*ch)) {
        ch++;
    }
    while(*ch != '\0') {
        value = append(value, *ch);
        ch++;
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
