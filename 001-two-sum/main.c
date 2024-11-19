#include "types.h"
#include "solution-1.h"
#include "test.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
    int argc;
    char ** argv;
} Args;

typedef struct {
    Algorithm algorithm;
} Options;


void fatal_error(char message[]) {
    puts(message);
    exit(EXIT_FAILURE);
}


void shift_args(Args * args) {
    --(args->argc);
    ++args->argv;
};


Algorithm parse_algorithm(Args * args) {

    static bool alg_given = false;
    if (alg_given) {
        fatal_error("Multiple --algorithm arguments are not allowed.");
    }

    if (args->argc <= 0) {
        fatal_error("An algorithm name must be specified.");
    }
        
    Algorithm algorithm;
    char * alg_name = args->argv[0];

    if (strcmp(alg_name, "double-loop") == 0) {
        algorithm = two_sum_double_loop;

    } else {
        // NOTE: Change this when adding a new algorithm
        fatal_error("The only supported algorithm is 'double-loop'.");
    }

    alg_given = true;
    shift_args(args);

    return algorithm;
}


void parse_option(Args * args, Options * options) {

    char * opt = args->argv[0];

    if (strcmp(opt, "--algorithm") == 0) {
        shift_args(args);
        options->algorithm = parse_algorithm(args);

    } else {
        fatal_error("Option not supported.");
    }
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
}


int main(int argc, char * argv[]) {

    Options options = {
        .algorithm = two_sum_double_loop
    };

    Args args = {
        .argc = argc,
        .argv = argv
    };
    parse_args(&args, &options);

    // TODO: Pass the Options struct instead
    test_algorithm(options.algorithm);

    return 0;
}