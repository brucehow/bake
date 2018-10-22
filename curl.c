#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "append.h"
#include "curl.h"

#define URLHEAD "urlheader"
#define CURLCMD "curl --head -v -o urlheader "
#define CURLLEN 29

void generateFile(char *url) {
    char *command;
    int lenUrl = strlen(url);

    command = malloc(CURLLEN * sizeof(char));
    strcpy(command, CURLCMD);
    command = realloc(command, (CURLLEN + lenUrl) * sizeof(char));
    strcat(command, url);
    execl("/bin/sh", "sh", "-c", command, NULL);
    free(command);
}

int getResponseCode(char *ch) {
    char *responseCode = NULL;

    while(*ch != '\0') {
        if(isspace(*ch)) {
            ch++;
            while(!isspace(*ch)) {
                responseCode = append(responseCode, *ch);
                ch++;
            }
            return atoi(responseCode);
        }
        ch++;
    }
    return 0;
}

// Gets the header for each line
char *getLineHeader(char *ch) {
      char *header = NULL;
      for(int i = 0; i < 14; i++) {
            header = append(header, *ch);
            ch++;
      }
      return header;
}

// Extract the date from the Last-Modified line
char *findLastModifiedDate(char *ch) {
    char *date = NULL;
    while(!isspace(*ch)){
        ch++;
    }
    ch++;
    while(*ch != '\0'){
        date = append(date, *ch);
        ch++;
    }
    return date;
}

time_t dateConvert(char *date) {
    struct tm tm;
    time_t epoch = 0;
    char buf[255];

    memset(&tm, 0, sizeof(struct tm));
    strptime(date, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    if(strptime(buf, "%Y-%m-%d %H:%M:%S", &tm) != NULL){
        epoch = mktime(&tm);
    }
    return epoch;
}

time_t getURLModDate(char *url) {
    generateFile(url);
    FILE *fp;
    char line[BUFSIZ];

    fp = fopen(URLHEAD, "r");
    if(fp == NULL) {
        perror(URLHEAD);
        exit(EXIT_FAILURE);
    }

    fgets(line, sizeof line, fp);
    int responseCode = getResponseCode(line);

    if(responseCode != 200) {
        fprintf(stderr, "URL: Response code %d returned\n", responseCode);
        exit(EXIT_FAILURE);
    }
    while(fgets(line, sizeof line, fp)) {
        if(strcasecmp(getLineHeader(line), "LAST-MODIFIED:") == 0) {
            return dateConvert(findLastModifiedDate(line));
        }
    }
    fprintf(stderr, "Failed to read URL modification date\n");
    exit(EXIT_FAILURE);
}
