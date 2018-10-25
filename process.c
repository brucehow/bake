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

/**
 * Reads the line and identifies the word prior to '=' or ':'. Iterates through
 * each char and reports to the user if an invalid word definition is used
 */
void readLine(char *ch) {
    char *word = NULL;
    // Excluding leading spaces
    while(isspace(*ch)) {
        ch++;
    }
    while(*ch != '\0') {
        // Build the word
        if(!isalpha(*ch) && !isdigit(*ch) && *ch != '.') {
            fprintf(stderr, "Invalid word character '%c'\n", *ch);
            exit(EXIT_FAILURE);
        }
        word = append(word, *ch);
        ch++;

        // Check for end of word
        while(isspace(*ch)) {
            ch++;
            // Spaces between words are not permitted
            if(!isspace(*ch) && *ch != ':' && *ch != '=') {
                fprintf(stderr, "Invalid line definition at '%s'\n", word);
                exit(EXIT_FAILURE);
            }
        }
        if(*ch == '=') {
            processVariableDef(word, ++ch);
            break;
        } else if(*ch == ':') {
            processTargetDef(word, ++ch);
            break;
        }
    }
    free(word);
}
