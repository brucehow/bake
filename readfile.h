/* CITS2002 Project 2018
 * Names:	Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Gets each line from a particular Bakefile ensuring that they are extended
 * where required
 * @param  bakefile The Bakefile to grab a line from
 * @return          The pointer to the start of a line
 */
char* readFile(FILE *bakefile);
