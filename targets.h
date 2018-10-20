/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct targetNode {
    char *target;
    char **dependencies;
    char **actions;
    int numDep; // Number of dependencies
    int numAct; // Number of actions
	struct targetNode *next;
} target;

extern target *targetList;
extern target *currentTarget;

target *lastTarget;

void processTargetDef(char *word, char *ch);
void processActionDef(char *ch);
