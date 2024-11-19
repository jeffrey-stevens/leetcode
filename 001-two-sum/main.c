#include "types.h"
#include "options.h"
#include "solution.h"
#include "test.h"


int main(int argc, char * argv[]) {

    Options options = {
        .algorithm = (Algorithm) twoSum
    };

    Args args = {
        .argc = argc,
        .argv = argv
    };
    parse_args(&args, &options);

    test_algorithm(options.algorithm);

    return 0;
}