/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trimLine(char *line) {
    while(*line != '\0') {
        if(*line == '\n' || *line == '\r') {
            *line = '\0';
            break;
        }
        line++;
    }
}

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
		trimLine(line); // Remove trailing \n \r
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
