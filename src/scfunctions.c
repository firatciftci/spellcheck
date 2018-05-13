#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "scfunctions.h"
#include "dictionary.h"
#include "word.h"

/* 
 *	Order of functions:
 *		I. Saving files
 *		II. Functions for editing strings (lines)
 *		III. Interactive Mode
 *		IV. Batch Mode
 *		V. Main Page
 */


/*
 *	I. Saving Files
 */

void save_corrections(char* filename, char** lines)
{
	FILE* f = fopen(filename,"w");
	int i = 0;
	while (lines[i] != NULL) {
		fprintf(f, "%s", lines[i]);
		i++;
	}
	fclose(f);
}

void save_page(char* filename, char** lines, int* quit)
{
	int i = 1;

	while (i) {
        shell_save();
		shell_prompt();
		i = 0;
		char* line;
		char** args;

		line = read_line();
		args = split_line(line);


		if (args == NULL || args [2] != NULL) { // More than 1 input, or no input
			shell_error("Please type in one of the indicated commands!");
			i = 1;
		} else if (!strcmp(args[0], "s")) {
			save_corrections(filename, lines);
			*quit = 0;
		} else if (!strcmp(args[0], "c")) {
			save_corrections(args[1], lines);
			*quit = 0;
		} else if (!strcmp(args[0], "r")) {
			*quit = 1;
		} else if (!strcmp(args[0], "q")) {
			*quit = 0;
		} else {
			shell_error("Please type in one of the indicated commands!");
			i = 1;
		}
	}
}

/*
 *	II. Functions for editing strings
 */

void underline_misspelled(char *tkn, char* underline)
{
	int j = strlen(tkn);
    int i = 0;
	for( ; i < j; i++) {
    	strcat(underline, "^");
	}
		strcat(underline, " ");
		// printf("start \n");
		// printf("%s", underline);
		// printf("end \n");

}

void underline_correct_spelling(char *tkn, char* underline)
{
	int j = strlen(tkn);
    int i = 0;
	for( ; i < j; i++) {
    		strcat(underline, " ");
	}
		strcat(underline, " ");

}



void add_to_badwords(char *badword, char** badwords)
{
	int i = 0;
	while(badwords[i] != NULL) {
		i++;
	}
	badwords[i] = badword;
	// printf("adding badword %s", badword);
	// printf("i is %d ", i);
}

//takes in a line, identifies incorrect words, and generates a string of underlines  
void parse_string(char* string, dict_t *dict, char *underline, char** badwords)
{
	char *tkn = strtok(string, " ,.-'\n'"); //words only separated by these punctuation
	while (tkn != NULL) {

		if (valid_word(tkn, dict) == 0){
			//printf("%s ", tkn);
			underline_misspelled(tkn, underline);
			add_to_badwords(tkn, badwords);
		}
		else if (valid_word(tkn, dict) == 1) {
			//printf("%s ", tkn);
			underline_correct_spelling(tkn, underline);
		}
		else {
			printf("error processing text");
		}
		tkn = strtok(NULL, " ,.-");
	}

}

//reference from https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
char* correct_line(char* line, char* old_word, char* new_word)
{
	char buffer[2000] = {0}; //again, we might need to modify our size estimates
	char *insert_point = &buffer[0];
	char *tmp = line;
	int old_length = strlen(old_word);
	int new_length = strlen(new_word);

	while(1) {
		char *p = strstr(tmp, old_word);

		if (p == NULL) {
			strcpy(insert_point, tmp);
			break;
		}

		memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;

		memcpy(insert_point, new_word, new_length);
		insert_point += new_length;

		tmp = p + old_length;
	}

	strcpy(line, buffer);

	// discuss with sarika

	char* c = strdup(line);
	return c;
}



//initialises each element in array (that stores misspelled words in a line) to NULL
void initialize_badwords(char **badwords, int length)
{
    int i = 0;
	for ( ; i < length; i++) {
    	badwords[i] = NULL; //initialize each element to be NULL
    }
}

/*
 *	III. Interactive Mode
 */

/* Functions needed for interactive mode */
char* edit_interactive(char* line, dict_t* dict)
{
    char *line_copy = malloc(strlen(line));
    strcpy(line_copy, line); //maintain a copy of the line to preserve original line: line will be parsed into individual words
    int max_no_suggestions = 2; //should the user decide this?


    int length = strlen(line) / 3; //approximate 3 chars per word to be safe
    char *badwords[length]; //generates an empty array where the misspelled words in a line will be stored
    initialize_badwords(badwords, length);

    char *underline = (char *)malloc(strlen(line + 1)); //generate an empty array where the underline will go
    underline[0] = '\0'; 
    //char underline[strlen(line)] = "";


    parse_string(line, dict, underline, badwords); //identify misspelled words and add to bad_word, 
    //add to underline function 
    
    printf("%s", line_copy);
    printf("\n");
    printf("%s", underline);
    printf("\n");



    // printf("Misspelled words in this sentence are: ");

    // int i = 0;
    // while(badwords[i] != NULL) {
    // 	printf("%d: %s ",i+1, badwords[i]);
    // 	i++;
    // }
    // printf("\n");
    // int number1;
    // printf("Enter the number value of the word you would like to change: ");
    // scanf("%d", &number1);

    char *suggestions[max_no_suggestions]; //generates empty array where suggestions will be filled
 
    int i = 0;

    //replacing words according to user suggestions
      while (badwords[i] != NULL) {
    	int success = generate_suggestions(badwords[i], dict, suggestions);

    	if(success != -1) {
    	printf("Possible replacements for word %s are: ", badwords[i]);
    	printf("1: No replacement ");
    	for (int j = 0; j < max_no_suggestions; j++) {
    		printf("%d : %s ", j+2, suggestions[j]);

    	}  	

       }

    
    //gets replacement choice from user
    int number2;
    printf("Enter the number of the replacement: ");

    int check = scanf("%d", &number2);
    assert(check >= 0);

    if (number2 != 1) { //1 if no replacement needed
    	printf("Replacing %s with %s \n", badwords[i], suggestions[number2-2]);
    	correct_line(line_copy, badwords[i], suggestions[number2-2]); //modifies line function
    	printf("Corrected sentence is: \n");
     	printf("%s \n", line_copy);
    }

	i++;	// added loop changer
  }

	return line_copy;
	// need a way for string to (a) preserve punctuations and (b) 
	// @Sarika this would be where the program needs replace_word, ignore_word, alternate_spelling
}


/* interctive mode - open file, parse and work on later */
char** interactive_mode(char* filename, dict_t* dict, int* quit) //will pass in dictionary later
{
	char** lines;

	lines = lineparse_file(filename);

	// step through phases
	int i=0;
	while (lines[i] != NULL) {	// potential error - one empty line in the middle of two full?	
		lines[i] = edit_interactive(lines[i], dict); //edit interactive is called for each line 
		i++;
	}

    *quit = 0;
	return lines;
}

/* 
	IV. Batch Mode
 */
// Adapted from sarika's edit_interactive
char* edit_batch(char* line, dict_t* dict, int verbosity)
{
    char *line_copy = malloc(strlen(line));
    strcpy(line_copy, line); //maintain a copy of the line to preserve original line: line will be parsed into individual words
    int max_no_suggestions = 1; //need only one suggestion

    int length = strlen(line)/3; //approximate 3 chars per word to be safe
    char *badwords[length]; //generates an empty array where the misspelled words in a line will be stored
    initialize_badwords(badwords, length);

    char *underline = (char *)malloc(strlen(line + 1)); //generate an empty array where the underline will go
    underline[0] = '\0'; 
    parse_string(line, dict, underline, badwords); //identify misspelled words and add to bad_word, 

    char *suggestions[max_no_suggestions]; //generates empty array where suggestions will be filled
 
    int i = 0;
    //replacing words, printing out if batch mode
      while (badwords[i] != NULL) {
    	int success = generate_suggestions(badwords[i], dict, suggestions);
	if (success == -1) suggestions[0] = badwords[i];
    	correct_line(line_copy, badwords[i], suggestions[0]);
	if (verbosity) printf("WORD:%s\t\t\tREPLACEMENT:%s\n", badwords[i], suggestions[0]);
	i++;
	}

	return line_copy;
}

char** batch_mode(char* filename, dict_t* dict, int* quit, int verbosity)
{
	if (verbosity) printf("\nBatch Mode: Verbose\n\n");

	char** lines;
	lines = lineparse_file(filename);
	// if lineparse_file returns NULL
	if (lines == NULL) {
		shell_error("file parsing error: check txt file");
		*quit=1;
	}

	int i=0;
	while (lines[i] != NULL) {
		if (verbosity) printf("Line number: %d\n",i+1);
		lines[i] = edit_batch(lines[i], dict, verbosity);
		i++;
	}

	return lines;
}

/*
	V. Main Page
 */


/* Prints help page. Returns to main page via loop in main function */
void help_page()
{
    shell_help();
	shell_prompt();

	read_line();
}

/* Check if file with name, given by string, exists */
int fileexists(const char* filename)
{
	struct stat buffer;
	return(stat(filename,&buffer)==0);
}

/* helper for main_page, determine input mode */

int change_mode(char* arg)
{
	int a = atoi(arg);
	switch (a) {
		case 1: return a;	// might be "
		case 2: return a;
		case 3: return a;
		default: // error case
			shell_error("Argument unrecognizeable: return to default interactive mode");		
	}
	return 3; 		// default is 3, given mode
}

void main_page(int* quit, int *mode, char* file_name, char* dict_name)
{
	char* line;
	char** args;

	while (!(*quit)) {
		shell_intro();
		shell_prompt();

		line = read_line();
		args = split_line(line);

		if (args == NULL || args [2] != NULL) { // 3 inputs, or no input
			shell_error("Please type in one of the indicated commands!");
			*quit = 0;
		} else if (!strcmp(args[0],"h")) { // Print help page and exit
			help_page();
			*quit = 0;
		} else if (!strcmp(args[0],"f")) { // Check valid file path, then exit. If not, redo loop
			if(!fileexists(args[1])) {
				shell_error("\n\nPlease enter a valid file path for a new edit target!");
				*quit = 0;
			} else {
			strcpy(file_name,args[1]);
			printf("\n\nInput file is now %s\n\n\n",file_name);
			*quit=1;
			}
		} else if (!strcmp(args[0],"d")) { // Check file path validity for dicitonary
			if(!fileexists(args[1])) {
				shell_error("Please enter a valid file path for a new dictionary!");
				*quit = 0;
			} else {
			dict_name=args[1];
			printf("\n\nDictionary file is now %s\n\n\n",dict_name);
			*quit = 0;
			}
		} else if (!strcmp(args[0],"q")) { // quit
			*quit = 2;
		} else if (!strcmp(args[0], "m")) { // change mode
			*mode = change_mode(args[1]);
			printf("Mode changed to %d\n",atoi(args[1]));
			if(!fileexists(file_name)) {
				*quit = 0;
			} else {
				*quit = 1;
			}
		} else { // input bad
			shell_error("Please type in one of the indicated commands!");
			*quit = 0;
		}

		free(line);
		free(args);
	}
}
