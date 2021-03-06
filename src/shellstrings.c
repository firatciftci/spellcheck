/* 
 * String printing library for the shell
 *
 * See shellstrings.h for function documentation.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "shellstrings.h"
#include "main_functions_home.h"
#include "log.c/src/log.h"

/* See shellstrings.h */
void shell_prompt(bool color) {
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
        printf(BOLDWHITE "\nPlease load a file to begin. "
               "Additionally, select an output mode and/or "
               "choose dictionary before running the program.\n\n" RESET);

        printf(BOLDWHITE "[f] [/path/file.txt]" RESET "       : Input text file\n");
        printf(BOLDWHITE "[d] [/path/dictionary.txt]" RESET " : Input custom dictionary file\n");
        printf(BOLDWHITE "[m] [number]" RESET "               : Mode [1 - Quiet, 2 - Verbose, 3 - Interactive]\n");
        printf(BOLDWHITE "[c]" RESET "                        : Enable/Disable color\n");
        printf(BOLDWHITE "[h]" RESET "                        : Help\n");
        printf(BOLDWHITE "[q]" RESET "                        : Quit program\n");
    }

    else {
        printf("\nPlease load a file to begin. "
               "Additionally, select an output mode and/or "
               "choose dictionary before running the program.\n\n");

        printf("[f] [/path/file.txt]       : Input text file\n");
        printf("[d] [/path/dictionary.txt] : Input custom dictionary file\n");
        printf("[m] [number]               : Mode [1 - Quiet, 2 - Verbose, 3 - Interactive]\n");
        printf("[c]                        : Enable/Disable color\n");
        printf("[h]                        : Help\n");
        printf("[q]                        : Quit program\n");
    }
}

/* See shellstrings.h */
void shell_save(bool color) {
    if (color == true) {
        printf(BOLDWHITE "\n[p]" RESET " : Print all modifications\n");
        printf(BOLDWHITE "[s]" RESET " : Save to existing file\n");
        printf(BOLDWHITE "[c]" RESET " : Save to custom file\n");
        printf(BOLDWHITE "[r]" RESET " : Re-edit file\n");
        printf(BOLDWHITE "[q]" RESET " : Quit program\n");
    }

    else {
        printf("\n[p] : Print all modifications\n");
        printf("[s] : Save to existing file\n");
        printf("[c] : Save to custom file\n");
        printf("[r] : Re-edit file\n");
        printf("[q] : Quit program\n");
    }
}

/* See shellstrings.h */
void shell_edit_success(bool color) {
    if (color == true) {
        printf(GREEN "\nSpellcheck complete.\n" RESET);
    }

    else {
        printf("\nSpellcheck complete.\n");
    }
}

/* See shellstrings.h */
void shell_print(char **lines) {
    int i = 0;

    while (lines[i] != NULL) {
        printf("%s", lines[i]);

        i++;
    }
}

/* See shellstrings.h */
void shell_input(char *filename, char *status, bool color) {
    if (color == true) {
        printf(BOLDWHITE "%s" RESET " has been accepted as " BOLDWHITE "%s" RESET ".\n", filename, status);
    }

    else {
        printf("%s has been accepted as %s.\n", filename, status);
    }
}

/* See shellstrings.h */
void shell_error(char *error_text, bool color) {
    if (color == true) {
        printf(RED "ERROR:" RESET " %s", error_text);
    }

    else {
        printf("ERROR: %s", error_text);
    }
}

/* See shellstrings.h */
void shell_usage(bool color) {
    if (color == true) {
        printf(RED "Usage:" RESET " ./spellcheck [filename.txt] [-mode] [-dictflag] [~/path/file.txt] [-saveflag] [~/path/destination.txt]\n");
    }

    else {
        printf("Usage: ./spellcheck [filename.txt] [-mode] [-dictflag] [~/path/file.txt] [-saveflag] [~/path/destination.txt]\n");
    }
}

/* See shellstrings.h */
void shell_help(bool color) {
    if (color == true) {
        printf(BOLDWHITE "------- Help Page ------\n" RESET

               "\nSpellcheck is a tool which searches for misspelled words "
               "and suggests alternative spellings given a text file.\n"

               "\nCurrently, you are in interactive mode. Return to the previous page to input a file.\n"

               "\nTo run in batch mode, exit the program with the command " BOLDWHITE "exit" RESET
               ", and run: " BOLDWHITE "$ ./spellcheck -i /path/file.txt" RESET ".\n"

               "\nFlags: " BOLDWHITE "-q" RESET " is for quiet, and " BOLDWHITE
               "-v" RESET " is for verbose.\n"

               "\nTo input a custom dictionary to the program, use " BOLDWHITE
               "-d /path/dictionary.txt" RESET ", and to provide a file saving destination, "
               "use " BOLDWHITE  "-s /path/filename.txt" RESET ".\n"

               "\nTo enable color inside the program, use the " BOLDWHITE "-c" RESET " flag.\n"

               BOLDWHITE "\nEnter any command to return to the previous page." RESET "\n");
    }

    else {
        printf("------- Help Page ------\n"

               "\nSpellcheck is a tool which searches for misspelled words "
               "and suggests alternative spellings given a text file.\n"

               "\nCurrently, you are in interactive mode. Return to the previous page to input a file.\n"

               "\nTo run in batch mode, exit the program with the command 'exit', "
               "and run: '$ ./spellcheck [-flag] /path/file.txt'.\n"

               "\nFlags: '-q' is for quiet, and '-v' is for verbose.\n"

               "\nTo input a custom dictionary to the program, use "
               "'-d /path/dictionary.txt', and to provide a file saving destination, "
               "use '-s /path/filename.txt'.\n"

               "\nTo enable color inside the program, use the '-c' flag.\n"

               "\n-- Enter any command to return to the previous page. --\n");
    }
}

/* See shellstrings.h */
void shell_start_interactive(char *filename, char *dict, char *md, bool color) {
    if (color == true) {
        log_info(BOLDWHITE "\n\n=============================================================\n"
                 "====================== Editing Started ======================\n"
                 "=============================================================\n\n" RESET);

        log_info(BOLDWHITE "File         :" RESET " %s\n"
                 BOLDWHITE "Dictionary   :" RESET " %s\n"
                 BOLDWHITE "Mode         :" RESET " %s\n", filename, dict, md);
    }

    else {
        log_info("\n\n=============================================================\n"
                 "====================== Editing Started ======================\n"
                 "=============================================================\n\n");

        log_info("File         : %s\n"
                 "Dictionary   : %s\n"
                 "Mode         : %s\n", filename, dict, md);
    }
}

/* See shellstrings.h */
char *shell_modename(int mode) {
    switch (mode) {
    case QUIET_MODE:
        return "Quiet Batch Mode";
    case VERBOSE_MODE:
        return "Verbose Batch Mode";
    case INTERACTIVE_MODE:
        return "Interactive Mode";
    default:
        break;
    }

    return "Interactive Mode";
}

/* See shellstrings.h */
void shell_interactive_line_print(int lnum, char *line, char *underline, bool returnflag, bool color) {
    if (color == true) {
        printf(BOLDWHITE "\nLine:" RESET " %d:\n%s" , lnum, line);

        if (returnflag) {
            printf("\n");
        }

        printf(BOLDRED "%s" RESET "\n", underline);
    }

    else {
        printf("\nLine: %d:\n%s", lnum, line);

        if (returnflag) {
            printf("\n");
        }

        printf("%s\n", underline);
    }
}

/* See shellstrings.h */
void shell_interactive_replacements(char *word, char **sug, bool color) {
    int j = 0;

    if (color == true) {
        if (sug == NULL) {
            sug[0] = word;
            printf("\nNo suggestions have been generated for " BOLDWHITE "%s" RESET ".\n\n", word);
            printf(BOLDWHITE "[d]" RESET " : Delete\n");
            printf(BOLDWHITE "[i]" RESET " : Input\n");
            printf(BOLDWHITE "[s]" RESET " : Skip\n\n");
        }

        else {
            printf("\nPossible replacements for word %s are:\n\n", word);

            while (sug[j] != NULL) {
                printf("[%d] : %s\n", j + 1, sug[j]);
                j++;
            }

            printf(BOLDWHITE "\n[d]" RESET " : Delete\n");
            printf(BOLDWHITE "[i]" RESET " : Input\n");
            printf(BOLDWHITE "[s]" RESET " : Skip\n\n");
        }
    }

    else {
        if (sug == NULL) {
            char** sug = calloc(2, sizeof(char*));
            sug[0] = word;
            printf("\nNo suggestions have been generated for %s.\n\n", word);
            printf("[d] : Delete\n");
            printf("[i] : Input\n");
            printf("[s] : Skip\n\n");
        }

        else {
            printf("\nPossible replacements for word %s are:\n\n", word);

            while (sug[j] != NULL) {
                printf("[%d] : %s\n", j + 1, sug[j]);

                j++;
            }

            printf( "\n[d] : Delete\n");
            printf( "[i] : Input\n");
            printf( "[s] : Skip\n\n");
        }
    }
}

/* See shellstrings.h */
void shell_verbose_chart(int lnum, char *line, char *misspelled, char **suggestions) {
    // Prints the location and character
    char* ptr = strstr(line, misspelled);
    int charpos = 0;
    charpos = ptr - line;

    log_trace("(shell_verbose_chart) Character position in line is %d.", charpos);

    printf("%d:%d\t\t\t", lnum, charpos);

    // Number of tabs
    int ntab = 3 - (strlen(misspelled) / 8);

    if (ntab < 0) {
        ntab = 1;
    }

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

    // Prints list of replacement
    printf("\n");
}

/* See shellstrings.h */
void shell_save_message(bool color) {
    if (color == true) {
        printf("\n" BOLDWHITE "Enter a file name [path/*.txt] or enter 'r' to return to previous page." RESET "\n");
    }

    else {
        printf("\nEnter a file name [path/*.txt] or enter 'r' to return to previous page.\n");
    }
}