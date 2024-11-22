#ifndef OPTIONS_H
#define OPTIONS_H

#include "types.h"

#include <stdbool.h>


typedef struct {
    int argc;
    char ** argv;
} Args;

typedef struct {
    Algorithm algorithm;
    bool randomize_seed;
    unsigned int seed;
    int num_max;
    int array_size_max;
} Options;


typedef void (*OptionHandler)(char * arg, Options *);


void register_option(const char * option_name, const bool requires_arg,
    const bool allow_multiple, OptionHandler option_handler);

void parse_args(Args * args, Options * options);

#endif