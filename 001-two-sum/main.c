#include "types.h"
#include "options.h"
#include "solution.h"
#include "test.h"

#include <stdbool.h>

const int RAND_SEED = 692;


int main(int argc, char * argv[]) {

    Options options = {
        .algorithm = (Algorithm) twoSum,
        .randomize_seed = false,
        .seed = RAND_SEED
    };

    Args args = {
        .argc = argc,
        .argv = argv
    };
    parse_args(&args, &options);

    test_algorithm(&options);

    return 0;
}