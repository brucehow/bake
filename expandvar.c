#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include "append.h"
#include "variables.h"
#include "expandvar.h"

// Value of PATH_MAX is 4096
#define PATH_MAX 4096

char *fetchVariable(char *var) {
    var += 2;

    if(strcmp(var, "PID") == 0) {
        int pid = getpid();
        int pidLen = floor(log10(abs(pid))) + 1;
        char *buffer = malloc(sizeof(char) * pidLen);
        sprintf(buffer, "%d", pid);
        return buffer;
    } else if(strcmp(var, "PPID") == 0) {
        int ppid = getppid();
        int ppidLen = floor(log10(abs(ppid))) + 1;
        char *buffer = malloc(sizeof(char) * ppidLen);
        sprintf(buffer, "%d", ppid);
        return buffer;
    } else if(strcmp(var, "PWD") == 0) {
        char *cwd = malloc(sizeof(char)*PATH_MAX);
        if(getcwd(cwd, sizeof(char)*PATH_MAX) != NULL) {
            return cwd;
        } else {
            perror("getcwd()");
            exit(EXIT_FAILURE);
        }
    } else if(strcmp(var, "RAND") == 0) {
        int num = rand();
        int numLen = floor(log10(abs(num))) + 1;
        char *buffer = malloc(sizeof(char) * numLen);
        sprintf(buffer, "%i", num);
        return buffer;
    } else if(strcmp(var, "HOME") == 0) {
        return getenv("HOME");
    }
    struct variableNode *it = variableList;
    while(it != NULL) {
        if(strcmp(it->variable, var) == 0) {
            return it->value;
        }
        it = it->next;
    }
    return "";
}

char *expandVariables(char *ch) {
    // Store the expanded line
    char *expanded = NULL;
    // Stores any var builds
    char *var = NULL;

    while(*ch != '\0') {
        // Look for the '$' char
        if(*ch != '$') {
            expanded = append(expanded, *ch);
            ch++;
            continue;
        }
        var = append(var, *ch);
        ch++;
        // Check for preceeding (
        if(*ch != '(') {
            var = append(var, *ch);
            strcat(expanded, var);
            var = NULL;
            continue;
        }
        // We have $(..
        var = append(var, *ch);
        ch++;
        while(*ch != ')' && *ch != '\0') {
            var = append(var, *ch);
            if(!isdigit(*ch) && !isalpha(*ch)) {
                strcat(expanded, var);
                var = NULL;
                ch++;
                continue;
            }
            ch++;
        }
        if(*ch == '\0') {
            strcat(expanded, var);
            return expanded;
        }
        strcat(expanded, fetchVariable(var));
        var = NULL;
        ch++;
    }
    free(var);
    return expanded;
}
