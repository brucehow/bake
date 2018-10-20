/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trim_line(char *line) {
    while(*line != '\0') {
        if(*line == '\n' || *line == '\r') {
            *line = '\0';
            break;
        }
        line++;
    }
}

char* read_file(FILE *bakefile) {
	char line[BUFSIZ];
    int len = 0;

    char *full_line = NULL;
    int full_len = 0;

	while(fgets(line, sizeof line, bakefile) != NULL) {
        // Exclude comment lines
        if(*line == '#') {
            continue;
        }
		trim_line(line); // Remove trailing \n \r
        len = strlen(line);
        full_len += len;

        if(full_line == NULL) {
            full_line = strdup(line);
        } else {
            full_line = realloc(full_line, full_len+1);
            strcat(full_line, line);
        }

        // Check for more continuation symbols
        if(full_line[full_len-1] != '\\') {
            break;
        }
        full_line[--full_len] = '\0';
	}
    return full_line;
}
