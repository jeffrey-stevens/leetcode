#include "types.h"
#include "error.h"
#include "options.h"
#include "solution.h"
#include "test.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>


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


static void parse_seed(Args * args, Options * options) {

    static bool opt_given = false;
    if (opt_given) {
        fatal_error("Multiple --seed arguments are not allowed.");
    }

    if (args->argc <= 0) {
        fatal_error("--seed requires an argument (either a non-negative integer or the value 'random').");
    }
        
    char * seed_arg = args->argv[0];

    if (strcmp(seed_arg, "random") == 0) {
        options->randomize_seed = true;

    } else {
        char * endptr;
        long seed = strtol(seed_arg, &endptr, 10);

        if (endptr == seed_arg || *endptr != '\0') {
            // There's an invalid character in the string
            fatal_error("The argument to --seed must be a non-negative integer or the value 'random'.");
        }

        // Check that the integer is within the range of a long int.
        // If it is out-of-range, strtol() will return either LONG_MIN or LONG_MAX,
        // and errono will be set to ERANGE.
        if ( seed < 0 || (unsigned long) seed > UINT_MAX || 
                (seed == LONG_MAX && errno == ERANGE) ) {
            fatal_error("The seed is out-of-range.");
        }

        // The seed should be save to convert to an unsigned int
        options->randomize_seed = false;
        options->seed = (unsigned int) seed;
    }

    opt_given = true;
    shift_args(args);
}


static void parse_option(Args * args, Options * options) {

    char * opt = args->argv[0];

    // if (strcmp(opt, "--algorithm") == 0) {
    //     shift_args(args);
    //     options->algorithm = parse_algorithm(args);

    // } else {
    //     fatal_error("Option not supported.");
    // }
    if (strcmp(opt, "--seed") == 0) {
        shift_args(args);
        parse_seed(args, options);

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