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

bool isUrl(char *dependency) {
    return(strstr(dependency, "http://") == dependency
    || strstr(dependency, "https://") == dependency
    || strstr(dependency, "file://") == dependency);
}

time_t getFileModDate(char *file) {
    stat(file, &statAttribute);
    fileAttribute = gmtime(&statAttribute.st_mtime);
    return(mktime(fileAttribute) + (8 * 60 * 60));
}
