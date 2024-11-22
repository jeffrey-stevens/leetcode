#include "options.h"
#include "option-handlers.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>


#define BUFFER_SIZE 256

const long MAX_NUM = 1000000000L;
const long MIN_ARRAY_SIZE = 2L;
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


typedef enum {
    PARSE_SUCCESS,
    PARSE_INVALID_FORMAT,
    PARSE_OUT_OF_RANGE
} ParseError;


static ParseError parse_int(char * arg, long min, long max, long * value) {

    errno = 0;

    char * endptr;
    long parsed_value = strtol(arg, &endptr, 10);

    if (endptr == arg || *endptr != '\0') {
        // There's an invalid character in the string
        return PARSE_INVALID_FORMAT;
    }

    // If the parsed value is out-of-range, strtol() will return either LONG_MIN
    // or LONG_MAX, and errono will be set to ERANGE.
    if ( parsed_value < min || parsed_value > max || 
            ((parsed_value == LONG_MIN || parsed_value == LONG_MAX) 
                && errno == ERANGE) ) {
        return PARSE_OUT_OF_RANGE;
    }

    *value = parsed_value;

    return PARSE_SUCCESS; 
}


void parse_seed(char * arg, Options * options) {

    if (strcmp(arg, "random") == 0) {
        options->randomize_seed = true;

    } else {
        long seed;
        const long seed_min = 0L;
        long seed_max = 
            ((unsigned long) LONG_MAX <= (unsigned long) UINT_MAX) 
                ? LONG_MAX : (long) UINT_MAX;

        ParseError err = parse_int(arg, seed_min, seed_max, &seed);

        if (err != PARSE_SUCCESS) {
            char msg[BUFFER_SIZE];
            snprintf(msg, BUFFER_SIZE, 
                "--seed requires an integer argument between"
                " %ld and %ld, inclusive.",
                seed_min, seed_max);
            fatal_error(msg);
        }

        // The seed should be safe to convert to an unsigned int
        options->randomize_seed = false;
        options->seed = (unsigned int) seed;
    }
}


void parse_num_max(char * arg, Options * options) {

    long num_max;
    const long num_lower_bound = 0L;
    long num_upper_bound = (MAX_NUM < (long) INT_MAX)
        ? MAX_NUM : (long) INT_MAX;

    ParseError err = parse_int(arg, num_lower_bound, num_upper_bound, &num_max);

    if (err != PARSE_SUCCESS) {
        char msg[BUFFER_SIZE];
        snprintf(msg, BUFFER_SIZE, 
            "--num-max requires an integer argument between"
            " %ld and %ld, inclusive.",
            num_lower_bound, num_upper_bound);
        fatal_error(msg);
    }
    
    // num_max should be safe to convert to an int
    options->num_max = (int) num_max;
}


void parse_array_size_max(char * arg, Options * options) {

    long array_size_max;
    long size_lower_bound = MIN_ARRAY_SIZE;
    // This probably isn't needed here since MAX_ARRAY_SIZE shouldn't be very large...
    long size_upper_bound = (MAX_ARRAY_SIZE < (long) INT_MAX)
        ? MAX_ARRAY_SIZE : (long) INT_MAX;

    ParseError err = parse_int(arg, size_lower_bound, size_upper_bound,
        &array_size_max);

    if (err != PARSE_SUCCESS) {
        char msg[BUFFER_SIZE];
        snprintf(msg, BUFFER_SIZE, 
            "--array-size-max requires an integer argument between"
            " %ld and %ld, inclusive.",
            size_lower_bound, size_upper_bound);
        fatal_error(msg);
    }

    // array_size_max should be safe to convert to an int
    options->array_size_max = (int) array_size_max;
}
