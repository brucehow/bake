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
    if(stat(file, &statAttribute) < 0) {
        return 0;
    }
    fileAttribute = gmtime(&statAttribute.st_mtime);
    return(mktime(fileAttribute));
}
