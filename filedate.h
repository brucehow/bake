#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


struct tm *fileAttribute;
struct stat statAttribute;

int compareModDate(char *target, char *dependency);
