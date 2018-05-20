#ifndef INCLUDE_MAIN_FUNCTIONS_H
#define INCLUDE_MAIN_FUNCTIONS_H

#include "parser.h"
#include "dictionary.h"
#include "word.h"
/* 
	Order of functions:
		I. Saving files
		II. Functions for editing strings (lines)
		III. Interactive Mode
		IV. Batch Mode
		V. Main Page
 */


/*
	I. Saving Files
 */
/*
 * save_corrections: writes lines (lines) to a file with name (filename)
 * parameters: name of file (saving destination), array of strings to be printed in file
 * returns: void
 */
void save_corrections(char* filename, char** lines);

/*
 * save_page: prints save_page, accepting command line inputs until save_file name is accepted, or
 * user chooses to return to page / quit
 * parameters:
 *      - name of file (saving destination)
 *      - array of strings to be printed in file
 *      - a pointer to an int, which is a flag to main indicating whether spellcheck should exit
 * returns: void
 */
void save_page(char* filename, char** lines, int* quit);

/*
	II. Functions for editing strings
*/
/*
 * underline_misspelled: generate "^" as underlines for misspelled words
 * parameters:
 *      - word to be underlined
 *      - underline (character "^" is added to underline, which is a string to be printed
 *      - below the line
 * returns: void
 */
void underline_misspelled(char *word, char* underline);

/*
 * underline_misspelled: generate " " as underlines for non-misspelled words
 * parameters:
 *      - word to be underlined
 *      - underline (character " " is added to underline)
 * returns: void
 */
void underline_correct_spelling(char *word, char* underline);

/*
 * underline_misspelled_sentence: given a list of bad words in order, underline them in sentence
 * paramters:
 *      - array of misspelled words
 *      - sentence to be edited
 *      - element
 * returns: underline for line
 */
char* underline_misspelled_sentence(char** misspelled, char* sentence, int element);

/*
 * add_to_misspelled: add an incorrect word to list of bad words
 * parameters:
 *      - word
 *      - list of misspelled words
 * returns: int
 */
int add_to_misspelled(char *word, char** misspelled);

/*
 * parse_string: parse string, generating underline and list of bad words
 * parameters:
 *      - string (line) to be parsed
 *      - dictionary
 *      - underline: function generates underline, tailored to array
 *      - misspelled: misspelled words in the line
 * return: int indicating successtakes in a line, identifies incorrect words and stores them in misspelled, and generates a string of underlines to be printed under that sentence
 */
int parse_string(char* string, dict_t *dict, char *underline, char** misspelled);

//reference from https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
/*
 * correct_line: replace word in array
 * parameters:
 *      - line to be edited
 *      - old word (misspelled)
 *      - new word (correction)
 * return: edited line 
 */
char* correct_line(char* line, char* old_word, char* new_word);

//initialises each element in array (that stores misspelled words in a line) to NULL
/*
 * initialize_misspelled: initialize array to be used in edit_interactive/edit_batch
 * parameters:
 *      - malloced array of misspelled words from interactive_mode
 *      - length of array
 * return: int indicating success
 */
int initialize_misspelled(char **misspelled, int length);

/*
	III. Interactive Mode

*/

/*
 * edit_interactive: returns a line which has been corrected accepting inptus from user
 * parameters:
 *      - line to be edited
 *      - dictionary
 *      - number of line
 * return: edited line
 */
char* edit_interactive(char* line, dict_t* dict, int linenumber);

/*
 * interctive mode: open file, parse and edit
 * parameters:
 *      - name of file to be parsed
 *      - dictionary
 *      - pointer to int quit, which is a flag indicating whether or not spellcheck should terminate
 *
 */
char** interactive_mode(char* filename, dict_t* dict, int* quit); //will pass in dictionary later

/* 
	IV. Batch Mode
 */
/*
 * edit_batch: returns a line which has been corrected with automatic suggestions
 * parameters:
 *      - string of line to be edited
 *      - dictionary
 *      - flag indicating whether or not to print output
 * verbosity determines whether or not shell output exists */
char* edit_batch(char* line, dict_t* dict, int verbosity);

/* 
 * batch_mode: operates batch mode
 * parameters: 
 *      - name of file to be parsed
 *      - dictionary
 *      - flag indicating whether or not quit spellcheck after operation
 *      - flag indicating whether or not to print output
 */
char** batch_mode(char* filename, dict_t* dict, int* quit, int verbosity);

/*
	V. Main Page
 */


/*
 * help_page: Prints help page at request of user from mawin. Returns to main page via loop in main function
 * parameters: none 
 * return_values: none
 */
void help_page();

/* 
 * fileexists: check if file with name, given by string, exists
 * parameter: filename
 * return: int (bool)
 */
int fileexists(const char* filename);

/*
 * change_mode: helper for main_page, determine input mode
 * parameter: command line input from main_page
 * return: number indicating mode
 */
int change_mode(char* arg);

/*
 * main_page: operates main page
 * parameter: 
 * return: void
 */
void main_page(int* quit, int *mode, char* file_name, char* dict_name);


#endif
