#ifndef __OPTIONS_H__
#define __OPTIONS_H__

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


void parse_args(Args * args, Options * options);

#endif