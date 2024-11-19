#include "types.h"

typedef struct {
    int argc;
    char ** argv;
} Args;

typedef struct {
    Algorithm algorithm;
} Options;


void parse_args(Args * args, Options * options);