#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


struct tm *fileAttribute;
struct stat statAttribute;

/**
 * Check if a specified dependency is a URL
 * @param  dependency The dependency to check
 * @return            True if the dependency is a URL, false otherwise
 */
bool isUrl(char *dependency);

/**
 * Gets the last modified date for a file
 * @param  file The file name
 * @return      The last modified date in epoch time
 */
time_t getFileModDate(char *file);
