// This wraps the twoSum function to prevent naming clashes.
// This allows the function to be (effectively) renamed without needing to
// modify the implementation.  Thus the implementation code can be copied
// directly into LeetCode without carrying over any baggage.

#include "solution-1.h"

static int* twoSum(int* nums, int numsSize, int target, int* returnSize);

#include "solution-1.c"

int * two_sum_double_loop(NumsArray nums, Target target, int * returnSize) {
    return twoSum(nums.array, nums.size, target.sum, returnSize);
}