#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <curl/curl.h>
#include "filedate.h"
#include "curl.h"

/**
 * Checks if a give string is a URL by seeing if it starts with the specified
 * URL prefixs
 */
bool isUrl(char *dependency) {
    return(strstr(dependency, "http://") == dependency
    || strstr(dependency, "https://") == dependency
    || strstr(dependency, "file://") == dependency);
}

/**
 * Uses stat to return the modified date of a file
 */
time_t getFileModDate(char *file) {
    if(stat(file, &statAttribute) < 0) {
        return 0;
    }
    fileAttribute = gmtime(&statAttribute.st_mtime);
    return(mktime(fileAttribute));
}
