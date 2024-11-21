#include "types.h"
#include "options.h"
#include "solution.h"
#include "test.h"

#include <stdbool.h>

const int RAND_SEED = 692;
const int DEFAULT_NUM_MAX = 100;
const int DEFAULT_ARRAY_SIZE_MAX = 20;


int main(int argc, char * argv[]) {

    Options options = {
        .algorithm = (Algorithm) twoSum,
        .randomize_seed = false,
        .seed = RAND_SEED,
        .num_max = DEFAULT_NUM_MAX,
        .array_size_max = DEFAULT_ARRAY_SIZE_MAX
    };

    Args args = {
        .argc = argc,
        .argv = argv
    };
    parse_args(&args, &options);

    test_algorithm(&options);

    return 0;
}