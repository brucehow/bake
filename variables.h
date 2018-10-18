/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct variable_node {
    char *variable;
    char *value;
	struct variable_node *next;
} VARIABLE;

extern VARIABLE *variable_list;
VARIABLE *last_variable;

void process_variable(char *word, char *ch);
