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
#include "append.h"

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
        word = append(word, *ch);
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
            process_variable_def(word, ++ch);
            break;
        } else if(*ch == ':') {
            printf("Target: %s\n", word);
            process_target_def(word, ++ch);
            break;
        }
    }
    free(word);
}
