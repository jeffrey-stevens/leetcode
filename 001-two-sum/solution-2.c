/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

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


IndexedValue * sorted_indices(int * nums, int numsSize) {

    IndexedValue * indexed_values = (IndexedValue *) malloc(numsSize * sizeof(IndexedValue));

    for (int i = 0; i < numsSize; i++) {
       indexed_values->value = nums[i];
       indexed_values->index = i; 
    }

    qsort(indexed_values, numsSize, sizeof(IndexedValue), compare_values);

    return indexed_values;
}


int* twoSum(int* nums, int numsSize, int target, int* returnSize) {

    // Create an array of indices and sort it by value
    IndexedValue * indexed_values = sorted_indices(nums, numsSize); 

    // Traverse the diagonal until the boundary is reached

    // Traverse the boundary, looking for the target

    free(indexed_values);
}