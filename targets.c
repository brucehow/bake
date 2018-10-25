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

/**
 * Adds the action line to the appropiate target. Dynamically allocates memory
 * to the LinkedList and targetNode to accomodate for just enough space
 */
void processActionDef(char *actLine) {
    actLine++; // Exclude leading tab
    if(currentTarget->numAct == 0) {
        currentTarget->actions = malloc(sizeof(char*));
        if(currentTarget->actions == NULL) {
            perror(__func__);
            exit(EXIT_FAILURE);
        }
        currentTarget->actions[0] = strdup(actLine);
        currentTarget->numAct++;
    } else {
        currentTarget->numAct++;
        currentTarget->actions = realloc(currentTarget->actions, currentTarget->numAct * sizeof(char*));
        if(currentTarget->actions == NULL) {
            perror(__func__);
            exit(EXIT_FAILURE);
        }
        currentTarget->actions[currentTarget->numAct-1] = strdup(actLine);
    }
}

/**
 * Adds a single dependency to the appropiate target. Dynamically allocates
 * memory to the LinkedList and targetNode to accomodate for just enough space
 */
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

/**
 * Reads the line after the ':' symbol of a target declaration and add the
 * appropiate dependecies if any, to the appropiate target
 */
void processTargetDef(char *word, char *dependencyLine) {
    target *new = calloc(1, sizeof(target));
    if(new == NULL) {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
    new->target = strdup(word);
    currentTarget = new;

    // Exclude leading spaces
    while(isspace(*dependencyLine)) {
        dependencyLine++;
    }

    // Build & add dependency
    char *dependency = NULL;
    while(*dependencyLine != '\0') {
        if(!isspace(*dependencyLine)) {
            dependency = append(dependency, *dependencyLine);
        } else if(dependency != NULL) {
            addDependency(dependency);
            dependency = NULL;
        }
        dependencyLine++;
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
