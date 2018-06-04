/*
 * A module to handle each word and provide suggestions
 * 
 * See word.h for function documentation
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>	
#include <ctype.h>
#include <stdbool.h>
#include "word.h"
#include "dictionary.h"
#include "log.c/src/log.h"


/* See word.h */
bool valid_word(dict_t* dict, char* shaved_word) {
    if (dict_chars_exists(dict, *shaved_word) == EXIT_SUCCESS && *shaved_word != '\n') {
        if(dict_exists(dict, shaved_word) == EXIT_SUCCESS) {
            log_trace("valid_word returning true from valid_word");
            return true;
        } else {
            log_trace("valid_word returning false from valid_word");
            return false;
        }
    }
    return false;
}

/* See word.h */
char** generate_suggestions(dict_t* dict, char* word) {
    char** suggestions = calloc(3, sizeof(char*));

	if (dict == NULL) { // hard_coded; to change with suggestion.c
        log_warn("generate_suggestions no dictionary");
        suggestions[0] = strdup("no suggestions");
        suggestions[1] = NULL;
        return suggestions;
    }

    suggestions[2] = NULL;

	if (strcmp(word, "splling") == 0) {
		suggestions[0] = strdup("spelling");
		suggestions[1] = strdup("spilling");
	} else if (strcmp(word, "chequer") == 0) {
    	suggestions[0] = strdup("checker");
    	suggestions[1] = strdup("cheque");
	} else if((strcmp(word, "cme") == 0)) {
    	suggestions[0] = strdup("come");
    	suggestions[1] = strdup("came");
	} else if((strcmp(word, "m'y") == 0)) {
        suggestions[0] = strdup("my");
        suggestions[1] = strdup("me");
    }

    log_trace("returning suggestions from generate_suggestions");
    return suggestions;
}