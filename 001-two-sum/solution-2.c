/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include "error.h"

#include <stdlib.h>


typedef struct {
    int value;
    int index;
} IndexedValue;


int compare_values(const void * arg1, const void * arg2) {
    IndexedValue * value1 = (IndexedValue *) arg1;
    IndexedValue * value2 = (IndexedValue *) arg2;

    if (value1->value > value2->value) {
        return 1;
    } else if (value1->value < value2->value) {
        return -1;
    } else {
        return 0;
    }
}


IndexedValue * sorted_nums(int * nums, int numsSize) {

    IndexedValue * indexed_values = (IndexedValue *) malloc(numsSize * sizeof(IndexedValue));

    if (indexed_values == NULL) {
        fatal_error("Unable to allocate memory for the array of indexed values.");
    }

    for (int i = 0; i < numsSize; i++) {
       indexed_values->value = nums[i];
       indexed_values->index = i; 
    }

    qsort(indexed_values, numsSize, sizeof(IndexedValue), compare_values);

    return indexed_values;
}


int* twoSum(int* nums, int numsSize, int target, int* returnSize) {

    int * solution = (int *) malloc(2 * sizeof(int));
    if (solution == NULL) {
        fatal_error("Unable to allocate memory for the solution array.");
    }
    int retSize;

    // Create an array of indices and sort it by value
    IndexedValue * indexed_values = sorted_nums(nums, numsSize); 

    // Traverse the edge of the upper triangular matrix until the boundary is reached
    int i = 0, j = 1;
    int sum = indexed_values[i].value + indexed_values[j].value;

    while (sum < target && j < numsSize - 1) {
        ++i;
        ++j;
        sum = indexed_values[i].value + indexed_values[j].value;
    }
    // This will be at either:
    // 1) The lower-right corner of the upper diagonal matrix (j = numsSize - 1)
    // 2) The first entry that's greater than or equal to the target 
    // 3) Both

    // Traverse the boundary, looking for the target
    while ( (sum < target && j < numsSize - 1) ||
            (sum > target && i > 0) ) {
        
        if (sum < target) {
            // Check the next element to the right of the present one
            ++j;
        } else {
            // sum > target
            // Check the next element above the present one
            --i;
        }
        sum = indexed_values[i].value + indexed_values[j].value;
    }

    if (sum == target) {
        // The solution is found!
        solution[0] = indexed_values[i].index;
        solution[1] = indexed_values[j].index;
        retSize = 2;
    } else {
        // There's no solution
        solution[0] = solution[1] = -1;
        retSize = 0;
    }

    free(indexed_values);

    *returnSize = retSize;
    return solution;
}