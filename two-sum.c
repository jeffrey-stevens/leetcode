/*
LeetCode Problem 001:  Two Sum
https://leetcode.com/problems/two-sum/description/
*/

#include <stdlib.h>
#include <stdio.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {

    int * result = (int *) malloc(2 * sizeof(int));

    if (result == NULL) {
        // Unable to allocate memory
        exit(EXIT_FAILURE);
    }
    result[0] = -1;
    result[1] = -1;

    int i, j;
    for (i = 0; i < numsSize - 1; ++i) {
        for (j = i + 1; j < numsSize; ++j) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                break;
            }
        }
    }

    *returnSize = 2;

    return result;
}
