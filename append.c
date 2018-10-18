/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "append.h"

char *append(char *word, char ch) {
    if(word == NULL) {
        word = malloc(2 * sizeof(char));
        if(word == NULL) {
            perror(__func__);
            exit(EXIT_FAILURE);
        }
        word[0] = ch;
        word[1] = '\0';
    } else {
        int len = strlen(word);
        word = realloc(word, (len+2) * sizeof(char));
        if(word == NULL) {
            perror(__func__);
            exit(EXIT_FAILURE);
        }
        word[len] = ch;
        word[len+1] = '\0';
    }
    return word;
}
