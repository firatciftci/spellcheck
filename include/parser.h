#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>
#include <stdlib.h>

/* Parsing Functions for Parsing Input Files */

/* returns with pointer to array of strings, each of which represent a line in a given file */
/* current limit to each string is 1000 characters */
/* return NULL if file could not be opened */
char** parse_file(char* filename);

/* Parsing functions for parsing command line inputs */
/* read a command line and return a string */
char* parse_read_line();

/*
   reference: https://github.com/brenns10/lsh/blob/master/src/main.c
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **parse_split_line(char *line);
#endif
