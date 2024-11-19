#include "types.h"
#include "error.h"
#include "options.h"
#include "solution.h"
#include "test.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


static void shift_args(Args * args) {
    --(args->argc);
    ++args->argv;
};


// static Algorithm parse_algorithm(Args * args) {

//     static bool alg_given = false;
//     if (alg_given) {
//         fatal_error("Multiple --algorithm arguments are not allowed.");
//     }

//     if (args->argc <= 0) {
//         fatal_error("An algorithm name must be specified.");
//     }
        
//     Algorithm algorithm;
//     char * alg_name = args->argv[0];

//     if (strcmp(alg_name, "double-loop") == 0) {
//         algorithm = two_sum_double_loop;

//     } else {
//         // NOTE: Change this when adding a new algorithm
//         fatal_error("The only supported algorithm is 'double-loop'.");
//     }

//     alg_given = true;
//     shift_args(args);

//     return algorithm;
// }


static void parse_option(Args * args, Options * options) {

    char * opt = args->argv[0];

    // if (strcmp(opt, "--algorithm") == 0) {
    //     shift_args(args);
    //     options->algorithm = parse_algorithm(args);

    // } else {
    //     fatal_error("Option not supported.");
    // }

    // TODO:  Change this when adding options
    fatal_error("Option not supported.");
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