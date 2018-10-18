/* CITS2002 Project 2018
 * Names:	Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "variables.h"

VARIABLE *variable_list = NULL;
VARIABLE *last_variable = NULL;

void process_variable_def(char *word, char *ch) {
    // Store variable definition in a new structure
    VARIABLE *new = malloc(sizeof(VARIABLE));
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
    while(*ch != '\n') {
        value = append(value, *ch);
        ch++;
    }
    // Store the value
    new->value = strdup(value);
    free(value);
    printf("Value: %s\n", new->value);
}
