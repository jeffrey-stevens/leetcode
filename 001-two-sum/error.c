#include "error.h"

#include <stdlib.h>
#include <stdio.h>


void fatal_error(char message[]) {
    puts(message);
    exit(EXIT_FAILURE);
}