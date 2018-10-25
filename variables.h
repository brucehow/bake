/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * LinkedList structure used to contain every variable and it's value
 */
typedef struct variableNode {
    char *variable;
    char *value;
	struct variableNode *next;
} variable;

// Global variables to allow access for other files
extern variable *variableList;

// Keep track of the last variable
variable *lastVariable;

/**
 * Assign the value to the specified variable
 * @param word    The word or target that was just found
 * @param valLine The string containing the values
 */
void processVariableDef(char *word, char *valLine);
