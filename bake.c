/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "bake.h"
#include "main.h"
#include "variables.h"
#include "targets.h"
#include "filedate.h"

void bake() {
	// Check if a target name was specified
	if(buildTarget == NULL) {
		buildTarget = targetList->target;
	}
	printf("%s\n", buildTarget);
}
