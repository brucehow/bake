#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "append.h"
#include "variables.h"

char *fetchVariable(char *var) {
    char *varName = NULL;
    var += 2;
    while(*var != ')') {
        varName = append(varName, *var);
        var++;
    }

    if(strcmp(varName, "PID")) {
        return itoa(getpid());
    } else if(strcmp(varName, "PPID")) {
        return getppid();
    } else if(strcmp(varName, "PWD")) {
        char cwd[BUFSIZ];
        if(getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd()");
            exit(EXIT_FAILURE);
        }
        return cwd;
    } else if(strcmp(varName, "RAND")) {
        return itoa(rand());
    } else if(strcmp(varName, "HOME")) {
        return getenv();
    }

    struct variableNode *it = variableList;
    while(it != NULL) {
        if(it->variable == varName) {
            return it->value;
        }
        it = it->next;
    }
    return "";
}

char *expandVariables(char *ch) {
    char *var = NULL;
    char *expanded = NULL;

    while(*ch != '\0') {
        if(*ch == '$') {
            var = append(var, *ch);
            ch++;
            // Exit if we reach the nullbyte
            if(*ch == '\0') {
                expanded = appendStr(expanded, var);
                return expanded;
            }
            // Is a variable
            if(*ch == '(') {
                var = append(var, *ch);

                // Check if the next char is valid
                ch++;
                if(*ch == '\0') {
                    expanded = appendStr(expanded, var);
                    return expanded;
                }  // Empty variable is not a variable
                else if(*ch == ')') {
                    expanded = appendStr(expanded, var);
                    var = NULL;
                    ch++;
                    continue;
                }

                ch--; // Backtracks to the open bracket;

                // Iterates until the end bracket is found
                while(*ch != ')') {
                    ch++;
                    if(*ch == '\0') {
                        expanded = appendStr(expanded, var);
                        return expanded;
                    } else if(isspace(*ch)) {
                        expanded = appendStr(expanded, var);
                        ch++;
                        continue;
                    }
                    var = append(var, *ch);
                }
                // Variable found
                expanded = appendStr(expanded, fetchVariable(var));
                var = NULL;
            } else {
                expanded = appendStr(expanded, var);
                var = NULL;
            }
        } else {
            expanded = append(expanded, *ch);
        }
        ch++;
    }
    free(var);
    return expanded;
}

int main(int argc, char *argv[]) {
    char *line = "hello my $(pid) is $(ppid)";
    char *x = expandVariables(line);
    printf("Extended: %s\n", x);
}
