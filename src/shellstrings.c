
/* 
 * String output functions to be used in the shell
 *
 * See shellstrings.h for function documentation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "shellstrings.h"

/* See shellstrings.h */
void shiell_prompt(bool color) {
    if (color == true) {
        printf(BOLDWHITE "\nspellcheck >" RESET " ");
    }

    else {
        printf("\nspellcheck > ");
    }
}

/* See shellstrings.h */
void shell_main_menu(bool color) {
    if (color == true) {
        printf(BOLDWHITE "------- Welcome to Spellcheck! ------\n\n"

                         "Please load a file to begin. "
                         "Additionally, select an output mode and/or "
                         "choose dictionary before running the program.\n\n" RESET);

        printf(BOLDWHITE "f [/path/file.txt]" RESET "       : Input text file\n");
        printf(BOLDWHITE "d [/path/dictionary.txt]" RESET " : Input custom dictionary file\n");
        printf(BOLDWHITE "m [number]" RESET "               : Mode [1 - Quiet, 2 - Verbose, 3 - Interactive]\n");
        printf(BOLDWHITE "h" RESET "                        : Help\n");
        printf(BOLDWHITE "q" RESET "                        : Quit program\n");
    }

    else {
        printf("------- Welcome to Spellcheck! ------\n\n"

               "Please load a file to begin. "
               "Additionally, select an output mode and/or "
               "choose dictionary before running the program.\n\n");

        printf("f [/path/file.txt]       : Input text file\n");
        printf("d [/path/dictionary.txt] : Input custom dictionary file\n");
        printf("m [number]               : Mode [1 - Quiet, 2 - Verbose, 3 - Interactive]\n");
        printf("h                        : Help\n");
        printf("q                        : Quit program\n");
    }
}

/* See shellstrings.h */
void shell_save(bool color) {
    if (color == true) {
        printf(BOLDWHITE "p" RESET " : Print all modifications\n");
        printf(BOLDWHITE "s" RESET " : Save to existing file\n");
        printf(BOLDWHITE "c" RESET " : Save to custom file\n");
        printf(BOLDWHITE "r" RESET " : Re-edit file\n");
        printf(BOLDWHITE "q" RESET " : Quit program\n");
    }

    else {
        printf("p : Print all modifications\n");
        printf("s : Save to existing file\n");
        printf("c : Save to custom file\n");
        printf("r : Re-edit file\n");
        printf("q : Quit program\n");
    }
}

/* See shellstrings.h */
void shell_edit_success(bool color) {
    if (color == true) {
        printf(GREEN "\nSpellcheck complete!\n" RESET);
    }

    else {
        printf("\nSpellcheck complete!\n");
    }
}

/* See shellstrings.h */
void shell_print(char **lines, bool color) {
    int i = 0;

    while (lines[i] != NULL) {
        printf("%s\n", lines[i]);
        i++;
    }
}

/* See shellstrings.h */
void shell_input(char *input_file, char *status, bool color) {
    char *input = "has been accepted as the input file for";
    printf("%s %s %s!\n", input_file, input, status);
}

/* See shellstrings.h */
void shell_error(char *error_text, bool color) {
    if (color == true) {
	   printf(RED "ERROR:" RESET " %s\n", error_text);
    }

    else {
        printf("ERROR: %s\n", error_text);
    }
}

/* See shellstrings.h */
char *shell_error_format() {
    char *error_format =
    "Please use designated format:\n"
    "./spellcheck [-f /path/file.txt] [-d /path/dictionary.txt] [-q or -v]\n"
    "For help, run without command line arguments and enter help page.";

    return error_format;
}

/* See shellstrings.h */
char *shell_error_dict(char *dict) {
    char *error_dict =
    "Trouble reading dictionary file ";
    strcat(error_dict, dict);

    return error_dict;
}

/* See shellstrings.h */
char *shell_error_exit() {
    char *error_exit =
    "Encountered an error -  Program exiting automatically.";

    return error_exit;
}

/* See shellstrings.h */
void shell_help(bool color) {
    if (color == true) {
        printf(BOLDWHITE "Spellcheck is a tool which searches for misspelled words "
               "and suggests alternative spellings given a text file.\n" RESET
               "Currently, you are in interactive mode. Return to the previous page to input a file.\n"
               "To run in batch mode, exit the program with the command " BOLDWHITE "exit" RESET
               ", and run: " BOLDWHITE "$ ./spellcheck [-flag] /path/file.txt.\n" RESET
               "Flags: " BOLDWHITE "-q" RESET " is for quiet, and " BOLDWHITE
               "-v" RESET " is for verbose.\n"
               "To input a custom dictionary to the program, use " BOLDWHITE 
               "-d /path/dictionary.txt" RESET ", and to provide a file saving destination, "
               "use " BOLDWHITE  "-s /path/filename.txt" RESET ".\n"

               BOLDWHITE "Enter any command to return to the previous page." RESET "\n");
    }

    else {
        printf("Spellcheck is a tool which searches for misspelled words "
               "and suggests alternative spellings given a text file.\n"
               "Currently, you are in interactive mode. Return to the previous page to input a file.\n"
               "To run in batch mode, exit the program with the command 'exit', "
               "and run: '$ ./spellcheck [-flag] /path/file.txt'.\n"
               "Flags: '-q' is for quiet, and '-v' is for verbose.\n"
               "To input a custom dictionary to the program, use " 
               "'-d /path/dictionary.txt', and to provide a file saving destination, "
               "use '-s /path/filename.txt'.\n"

               "Enter any command to return to the previous page.\n");
    }
}

void shell_start_interactive(char *filename, char *dict, char *md, bool color) {
    if (color == true) {
        printf(BOLDWHITE "File         :" RESET " %s\n"
               BOLDWHITE "Dictionary   :" RESET " %s\n"
               BOLDWHITE "Mode         :" RESET " %s\n", filename, dict, md);
    }

    else {
        printf("File         : %s\n"
               "Dictionary   : %s\n"
               "Mode         : %s\n", filename, dict, md);
    }
}

char *shell_modename(int mode) {
    switch (mode) {
        case 1: return "Quiet Batch Mode";
        case 2: return "Verbose Batch Mode";
        case 3: return "Interactive Mode";
        default: break;
    }
    return "Interactive Mode";
}

void shell_interactive_line_print(int lnum, char *line, char *underline, int returnflag, bool color) {
    if (color == true) {
        printf(BOLDWHITE "Location:" RESET " %d:%s\n" , lnum, line);

        // if (returnflag) {
        //     printf("\n");
        // }

        printf(BOLDRED "%s" RESET "\n", underline);
    }

    else {
        printf("Location: %d:%s\n", lnum, line);

        // if (returnflag) {
        //     printf("\n");
        // }

        printf("%s\n", underline);
    }
}


void shell_interactive_replacements(char *word, char **sug, int flag, bool color) {
    int j = 0;

    if (flag == EXIT_FAILURE) {
        sug[0] = word;
        printf("No suggestions have been generated for " BOLDWHITE "%s" RESET ".\n", word);
        printf(BOLDWHITE "d" RESET " : Delete existing word.\n");
        printf(BOLDWHITE "i" RESET " : Input new word.\n");
        printf(BOLDWHITE "s" RESET " : Skip word replacement.\n");
    }

    else {
        printf("\nPossible replacements for word %s are:\n", word);

        while (sug[j] != NULL) {
            printf("%d : %s \n", j + 1, sug[j]);
            j++;
        }

        printf(BOLDWHITE "d" RESET " : Delete existing word.\n");
        printf(BOLDWHITE "i" RESET " : Input new word.\n");
        printf(BOLDWHITE "s" RESET " : Skip word replacement.\n");
    }
}

void shell_verbose_chart(int lnum, char *misspelled, char **suggestions) {
    printf("%d\t\t\t", lnum); // print line number
    
    int ntab = 3 - (strlen(misspelled) / 8); // number of tabs
    
    int j;
    
    printf("%s", misspelled);
    
    for (j = 0; j < ntab; j++) {
        printf("\t");
    }

    j = 0;

    while (suggestions[j] != NULL) {
        printf("%s", suggestions[j]);

        if (suggestions[j + 1] != NULL) {
            printf(", ");
        }

        j++;
    }

    printf("\n"); // print list of replacement
}

void shell_save_message(bool color) {
    if (color == true) {
        printf("\n" BOLDWHITE "Enter a file name [path/*.txt] or enter 'r' to return to previous page." RESET "\n");
    }

    else {
        printf("\nEnter a file name [path/*.txt] or enter 'r' to return to previous page.\n");
    }

    shell_prompt(color);
}