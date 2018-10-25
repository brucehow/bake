/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * LinkedList structure used to contain every target and their respective
 * actions and dependecies
 */
typedef struct targetNode {
    char *target;
    char **dependencies;
    char **actions;
    int numDep; // Number of dependencies
    int numAct; // Number of actions
	struct targetNode *next;
} target;

// Global variables to allow access for other files
extern target *targetList;
extern target *currentTarget;

// Keep track of the last variable
target *lastTarget;

/**
 * Adds every declaration if any to a particular target
 * @param word           The word or target that was just found
 * @param dependencyLine The string containing the dependecies
 */
void processTargetDef(char *word, char *dependencyLine);

/**
 * Adds every action if any to the target that was just processed
 * @param actLine The string containing the actions
 */
void processActionDef(char *actLine);
