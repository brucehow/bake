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
#define CURLCMD "curl --head -s -o urlheader "
#define CURLLEN 29

void generateFile(char *url) {
    char *command = malloc(CURLLEN * sizeof(char));
    strcpy(command, CURLCMD);
    command = realloc(command, (CURLLEN + strlen(url)) * sizeof(char));
    strcat(command, url);

    switch(fork()) {
		case -1: // Process creation failed
			perror("Fork");
			exit(EXIT_FAILURE);
		case 0: // Child process
			execl("/bin/sh", "sh", "-c", command, NULL);
			perror("execl");
			exit(EXIT_FAILURE);
		default: {
			int status;
			wait(&status);
			if(WEXITSTATUS(status) != 0) {
				fprintf(stderr, "URL: Failed to generate urlheader file for '%s'\n", url);
				exit(EXIT_FAILURE);
			}
		}
	}
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
    return -1; // Return -1 if no responseCode is found
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
        fprintf(stderr, "URL: Response code %d returned for '%s'\n", responseCode, url);
        exit(EXIT_FAILURE);
    }
    char *lineHeader = NULL;
    while(fgets(line, sizeof line, fp)) {
        lineHeader = getLineHeader(line);
        if(strcasecmp(lineHeader, "LAST-MODIFIED:") == 0) {
            time_t converted = dateConvert(findLastModifiedDate(line));
            fclose(fp);
            return converted;
        }
        lineHeader = NULL;
    }
    free(lineHeader);
    fprintf(stderr, "Failed to read URL modification date\n");
    exit(EXIT_FAILURE);
}
