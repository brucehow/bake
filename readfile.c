/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Removes trailing \n and \r symbols in a line prior to the \0 symbol
 */
void trimLine(char *line) {
    while(*line != '\0') {
        if(*line == '\n' || *line == '\r') {
            *line = '\0';
            break;
        }
        line++;
    }
}

/**
 * Reads each line from a given file and checks if the last character contains
 * the extension line char, '\'. Extends the line to the next line accordingly.
 * Comment lines, starting with '#' are excluded at this point
 */
char* readFile(FILE *bakefile) {
	char line[BUFSIZ];
    int len = 0;

    char *fullLine = NULL;
    int fullLen = 0;

	while(fgets(line, sizeof line, bakefile) != NULL) {
        // Exclude comment lines
        if(*line == '#') {
            continue;
        }
		trimLine(line);
        len = strlen(line);
        fullLen += len;

        if(fullLine == NULL) {
            fullLine = strdup(line);
        } else {
            fullLine = realloc(fullLine, fullLen+1);
            strcat(fullLine, line);
        }

        // Check for more continuation symbols
        if(fullLine[fullLen-1] != '\\') {
            break;
        }
        fullLine[--fullLen] = '\0';
	}
    return fullLine;
}
