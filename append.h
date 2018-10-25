/* CITS2002 Project 2018
 * Names: Bruce How, Vincent Tian
 * Student numbers:	22242664, 22262122
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Appends a char to a string by dynamically allocating memory
 * @param  word Initial string to append to
 * @param  ch   Char to append
 * @return      The string with the appended char
 */
char *append(char *word, char ch);

/**
 * Appends a string to a string by dynamically allocating memory
 * @param  word Initial string to append to
 * @param  add  String to append
 * @return      The string with the appended string
 */
char *appendStr(char *word, char *add);
