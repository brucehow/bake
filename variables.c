/* CITS2002 Project 2018
 * Names:	Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "variables.h"
#include "process.h"

VARIABLE *variable_list = NULL;
VARIABLE *last_variable = NULL;

char *strdup(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if(dup)
    {
        strcpy(dup, str);
    }
    return dup;
}

void process_variable(char *word, char *ch) {
    // Store variable in a new structure
    VARIABLE *new = malloc(sizeof(VARIABLE));
    if(new == NULL) {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
    new -> variable = strdup(word);

    // Build the value
    char *value = NULL;
    while(isspace(*ch)) {
        ch++;
    }
    while(*ch != '\n') {
        value = memory_management(value, ch);
        ch++;
    }
    new -> value = strdup(value);
    free(value);
    printf("Value: %s\n", new -> value);
}
