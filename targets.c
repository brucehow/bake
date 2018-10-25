/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numDepbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "targets.h"
#include "append.h"

target *targetList = NULL;
target *lastTarget = NULL;

// Target to add actions/dependencies to
target *currentTarget = NULL;

void processActionDef(char *ch) {
    ch++; // Exclude leading tab
    if(currentTarget->numAct == 0) {
        currentTarget->actions = malloc(sizeof(char*));
        if(currentTarget->actions == NULL) {
            perror(__func__);
            exit(EXIT_FAILURE);
        }
        currentTarget->actions[0] = strdup(ch);
        currentTarget->numAct++;
    } else {
        currentTarget->numAct++;
        currentTarget->actions = realloc(currentTarget->actions, currentTarget->numAct * sizeof(char*));
        if(currentTarget->actions == NULL) {
            perror(__func__);
            exit(EXIT_FAILURE);
        }
        currentTarget->actions[currentTarget->numAct-1] = strdup(ch);
    }
}

void addDependency(char *dependency) {
    if(currentTarget->numDep == 0) {
        currentTarget->numDep++;
        currentTarget->dependencies = malloc(sizeof(char*));
        if(currentTarget->dependencies == NULL) {
            perror(__func__);
            exit(EXIT_FAILURE);
        }
        currentTarget->dependencies[0] = strdup(dependency);
    } else {
        currentTarget->numDep++;
        currentTarget->dependencies = realloc(currentTarget->dependencies, currentTarget->numDep * sizeof(char*));
        if(currentTarget->dependencies == NULL) {
            perror(__func__);
            exit(EXIT_FAILURE);
        }
        currentTarget->dependencies[currentTarget->numDep-1] = strdup(dependency);
    }
}

void processTargetDef(char *word, char *ch) {
    target *new = calloc(1, sizeof(target));
    if(new == NULL) {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
    new->target = strdup(word);
    currentTarget = new;

    // Exclude leading spaces
    while(isspace(*ch)) {
        ch++;
    }

    // Build & add dependency
    char *dependency = NULL;
    while(*ch != '\0') {
        if(!isspace(*ch)) {
            dependency = append(dependency, *ch);
        } else if(dependency != NULL) {
            addDependency(dependency);
            dependency = NULL;
        }
        ch++;
    }
    if(dependency != NULL) {
        addDependency(dependency);
        free(dependency);
    }

    // Add the target to the list
    if(targetList == NULL) {
        targetList = new;
        lastTarget = new;
    } else {
        lastTarget->next = new;
        lastTarget = new;
    }
}
