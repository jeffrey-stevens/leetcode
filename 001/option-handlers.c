#include "options.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>


#define BUFFER_SIZE 256

const long MAX_NUM = 1000000000L;
const long MAX_ARRAY_SIZE = 10000L;


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

        // The seed should be safe to convert to an unsigned int
        options->randomize_seed = false;
        options->seed = (unsigned int) seed;
    }

    opt_given = true;
    shift_args(args);
}


static void parse_num_max(Args * args, Options * options) {

    static bool opt_given = false;
    if (opt_given) {
        fatal_error("Multiple --num-max arguments are not allowed.");
    }

    long num_upper_bound = (MAX_NUM < INT_MAX) ? MAX_NUM : INT_MAX;

    char out_of_range_msg[BUFFER_SIZE];
    int chars_written = snprintf(out_of_range_msg, BUFFER_SIZE, 
        "--num-max requires a integer argument between 0 and %ld, inclusive.",
        num_upper_bound);
    // Check that chars_written makes sense

    if (args->argc <= 0) {
        fatal_error(out_of_range_msg);
    }
        
    char * num_max_arg = args->argv[0];

    // Parse the integer
    char * endptr;
    long num_max = strtol(num_max_arg, &endptr, 10);

    if (endptr == num_max_arg || *endptr != '\0') {
        fatal_error(out_of_range_msg);
    }

    if ( num_max < 0 || num_max > (long) num_upper_bound || 
        (num_max == LONG_MAX && errno == ERANGE) ) {
        fatal_error(out_of_range_msg);
    }
    
    // num_max should be safe to convert to an int
    options->num_max = (int) num_max;

    opt_given = true;
    shift_args(args);
}


static void parse_array_size_max(Args * args, Options * options) {

    static bool opt_given = false;
    if (opt_given) {
        fatal_error("Multiple --array_size_max arguments are not allowed.");
    }

    // This probably isn't needed here since MAX_ARRAY_SIZE shouldn't be very large...
    long size_upper_bound = (MAX_ARRAY_SIZE < INT_MAX) ? MAX_ARRAY_SIZE : INT_MAX;

    char out_of_range_msg[BUFFER_SIZE];
    int chars_written = snprintf(out_of_range_msg, BUFFER_SIZE, 
        "--array-size-max requires a integer argument between 2 and %ld, inclusive.",
        size_upper_bound);
    // Check that chars_written makes sense

    if (args->argc <= 0) {
        fatal_error(out_of_range_msg);
    }

    char * array_size_max_arg = args->argv[0];

    // Parse the integer
    char * endptr;
    long array_size_max = strtol(array_size_max_arg, &endptr, 10);

    if (endptr == array_size_max_arg || *endptr != '\0') {
        fatal_error(out_of_range_msg);
    }

    if ( array_size_max < 2 || array_size_max > (long) size_upper_bound || 
        (array_size_max == LONG_MAX && errno == ERANGE) ) {
        fatal_error(out_of_range_msg);
    }

    // array_size_max should be safe to convert to an int
    options->array_size_max = (int) array_size_max;

    opt_given = true;
    shift_args(args);
}
