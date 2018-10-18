/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct target_node {
    char *target;
    char **dependencies;
    int num;
    char *action;
	struct target_node *next;
} TARGET;

extern TARGET *target_list;
extern TARGET *cur_target;

TARGET *last_target;

void process_target(char *word, char *ch);
