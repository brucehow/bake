#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

/**
 * Performs all variable expansions on a given line. The empty string is
 * inserted if the variable defeinition does not exist.
 * @param  ch The string containing zero or more variable expansions
 * @return    The string containing all expanded variable expansions
 */
char *expandVariables(char *ch);
