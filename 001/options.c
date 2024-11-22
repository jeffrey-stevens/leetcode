#include "types.h"
#include "error.h"
#include "options.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>


#define BUFFER_SIZE 256



typedef struct OptionsNodeStruct OptionsNode;

struct OptionsNodeStruct {
    char * option_name;
    bool requires_arg;
    bool allow_multiple;
    OptionHandler option_handler;
    bool opt_already_given;
    OptionsNode * next;
};


// Does this really need to be global?
static OptionsNode * options_register = NULL;


static void shift_args(Args * args) {
    --(args->argc);
    ++args->argv;
};


void register_option(const char * option_name, const bool requires_arg,
    const bool allow_multiple, OptionHandler option_handler) {

    OptionsNode * options_node = (OptionsNode *) malloc(sizeof(OptionsNode));
    if (options_node == NULL) {
        fatal_error(
            "Unable to allocate memory for the command-line options register."
        );
    }

    options_node->option_name = option_name;
    options_node->requires_arg = requires_arg;
    options_node->allow_multiple = allow_multiple;
    options_node->option_handler = option_handler;
    options_node->opt_already_given = false;

    // This places the current node at the head of the list.
    // Consequently, it will register options in reverse order (which shouldn't
    // matter much in this case).
    OptionsNode * old_register = options_register;
    options_register = options_node;
    options_node->next = old_register;
}


void free_options_register() {
    OptionsNode * curr_node = options_register;
    OptionsNode * next_node;
    while (curr_node != NULL) {
       next_node = curr_node->next; 
       free(curr_node);
       curr_node = next_node;
    }
}


static OptionsNode * find_option(char * option_name) {
    OptionsNode * curr_option = options_register;

    while ( curr_option != NULL
            && strcmp(curr_option->option_name, option_name) != 0 ) {
        curr_option = curr_option->next;
    }

    // Note that this will return NULL if the option isn't found
    return curr_option;
}


static void parse_option(Args * args, Options * options) {

    char * option_name = args->argv[0];

    OptionsNode * option_node = find_option(option_name);

    if (option_node == NULL) {
        // The option wasn't found in the options register
        fatal_error("Option not supported.");
    }

    if (!option_node->allow_multiple && option_node->opt_already_given) {
        fatal_error("The option can only be given once.");
    }

    if (option_node->requires_arg) {
        shift_args(args);

        if (args->argc <= 0) {
            fatal_error("The option requires an argument.");
        } else {
            char * opt_arg = args->argv[0];
            option_node->option_handler(opt_arg, options);
            shift_args(args);
        }
    }

    option_node->opt_already_given = true;
}


void parse_args(Args * args, Options * options) {

    // The first argument is the command; skip over this
    shift_args(args);

    char * currarg;
    while (args->argc > 0) {
        currarg = args->argv[0];

        if (currarg[0] == '-') {
            parse_option(args, options);

        } else {
            fatal_error("Invalid argument.");
        }
    }

    // The command-line options register is no longer necessary
    free_options_register();
}