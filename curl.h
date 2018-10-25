#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

/**
 * Gets the last modified date of a given URL
 * @param  url The URL string to fetch the modified date for
 * @return     The last modified date in epoch time or 0 if the URL is invalid
 */
time_t getURLModDate(char *url);
