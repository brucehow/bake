/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct variableNode {
    char *variable;
    char *value;
	struct variableNode *next;
} variable;

extern variable *variableList;
variable *lastVariable;

void processVariableDef(char *word, char *ch);
