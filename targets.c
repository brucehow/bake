/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student num_dbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "targets.h"
#include "append.h"

TARGET *target_list = NULL;
TARGET *last_target = NULL;

// Target to add actions/dependencies to
TARGET *current_target = NULL;

void add_dependecy(char *dependency) {
    if(current_target->num_d == 0) {
        current_target->dependencies = malloc(sizeof(char*));
        current_target->dependencies[0] = malloc(sizeof(char) * strlen(dependency));
        current_target->dependencies[0] = strdup(dependency);
        current_target->num_d++;
    } else {
        current_target->num_d++;
        current_target->dependencies = realloc(current_target->dependencies, current_target->num_d * sizeof(char*));
        current_target->dependencies[current_target->num_d] = malloc(sizeof(char) * strlen(dependency));
        current_target->dependencies[current_target->num_d] = strdup(dependency);
    }
}

void process_target_def(char *word, char *ch) {
    TARGET *new = malloc(sizeof(TARGET));
    if(new == NULL) {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
    new->target = strdup(word);
    current_target = new;

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
            add_dependecy(dependency);
            dependency = NULL;
        }
        ch++;
    }
    add_dependecy(dependency);
    free(dependency);

    // Add the target to the list
    if(target_list == NULL) {
        target_list = new;
        last_target = new;
    } else {
        last_target->next = new;
        last_target = new;
    }
}

void process_action_def(char *ch) {
    ch++; // Exclude leading tab

    if(current_target->num_a == 0) {
        current_target->actions = malloc(sizeof(char*));
        current_target->actions[0] = malloc(sizeof(char) * strlen(ch));
        current_target->actions[0] = strdup(ch);
        current_target->num_a++;
    } else {
        current_target->num_a++;
        current_target->actions = realloc(current_target->actions, current_target->num_a * sizeof(char*));
        current_target->actions[current_target->num_a] = malloc(sizeof(char) * strlen(ch));
        current_target->actions[current_target->num_a] = strdup(ch);
    }
}
