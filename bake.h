/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

/**
 * Builds a target based on the specified dependecies and its respective actions. If there are no targets, Bake will exit and inform the user.
 * @param targetToBuild The target to build. If none is specified, Bake will
 *                      build the first target
 */
void bake(char *targetToBuild);
