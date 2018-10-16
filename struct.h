/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Structures
typedef struct variableItem {
	char *key;
	char *value;
	struct variableItem *next;
} VARIABLE;

typedef struct targetItem {
	char *target;
	char *dependencies;
	struct targetItem *next;
} TARGET;

// Variables
extern VARIABLE *varables;
extern TARGET *targets;

// Methods
void addVariable(char *var, char *value);
void addTarget(char *var, char* value);
void debug();
