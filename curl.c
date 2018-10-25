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
#define CURL "curl --head -s -o urlheader "
#define CMDLEN 29
#define HEADLEN 14

/**
 * Executes the curl command in bash to generate a file containing a particular * URL's header information. If the URL is not found, an error is reported to
 * the user.
 */
void generateFile(char *url) {
    char *command = malloc(CMDLEN * sizeof(char));
    strcpy(command, CURL);
    command = realloc(command, (CMDLEN + strlen(url)) * sizeof(char));
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

/**
 * Gets the response code from the line containing the HTTP response by
 * iterating through until a space is found, and then building the response code
 */
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

/**
 * Grabs the first few characters in a given line which would normally contain the Line-Modified text
 */
char *getLineHeader(char *ch) {
      char *header = NULL;
      for(int i = 0; i < HEADLEN; i++) {
            header = append(header, *ch);
            ch++;
      }
      return header;
}

/**
 * Grabs the date from the Last-Modified line in the URL header file. Assumes
 * that the format of the Last-Modified line works in a way where the Date
 * beings after the first space character
 */
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

/**
 * Converts a string date into epoch time using the strptime() and mktime()
 * functions
 */
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

/**
 * Gets the modification date of a URL by employing all the helper functions
 * above. The function uses curl to grab a URL's header file and returns then
 * last modified date of the given URL in epoch time
 */
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
    fclose(fp);
    free(lineHeader);
    fprintf(stderr, "Failed to read URL modification date for '%s'\n", url);
    exit(EXIT_FAILURE);
}
