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

void process_variable(char *word, char *ch) {
    // Store variable in a new structure
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
        if(value == NULL) {
            value = malloc(2 * sizeof(char));
            if(value == NULL) {
                perror(__func__);
                exit(EXIT_FAILURE);
            }
            value[0] = *ch;
            value[1] = '\0';
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
        ch++;
    }
    new->value = strdup(value);
    free(value);
    printf("Value: %s\n", new->value);
}
