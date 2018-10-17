/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "process.h"
#include "variables.h"
#include "targets.h"

void process_line(char *ch) {
    char *word = NULL;

    // Excluding leading spaces
    while(isspace(*ch)) {
        ch++;
    }
    while(*ch != '\n') {
        // Build the word
        if(!isalpha(*ch) && !isdigit(*ch) && *ch != '.') {
            fprintf(stderr, "Invalid declaration character '%c'\n", *ch);
            exit(EXIT_FAILURE);
        }
        if(word == NULL) {
            word = malloc(2 * sizeof(char));
            if(word == NULL) {
                perror(__func__);
                exit(EXIT_FAILURE);
            }
            word[0] = *ch;
            word[1] = '\0';
        } else {
            int len = strlen(word);
            word = realloc(word, (len+2) * sizeof(char));
            if(word == NULL) {
                perror(__func__);
                exit(EXIT_FAILURE);
            }
            word[len] = *ch;
            word[len+1] = '\0';
        }
        ch++;

        // Check for end of word
        while(isspace(*ch)) {
            ch++;
            // Spaces between words are not permitted
            if(!isspace(*ch) && *ch != ':' && *ch != '=') {
                fprintf(stderr, "Invalid declaration line at '%s'\n", word);
                exit(EXIT_FAILURE);
            }
        }
        if(*ch == '=') {
            printf("Variable: %s\n", word);
            process_variable(word, ++ch);
            break;
        } else if(*ch == ':') {
            printf("Target: %s\n", word);
            process_target(word, ++ch);
            break;
        }
    }
    free(word);
}
