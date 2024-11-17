#include "two-sum.c"

#include <stdlib.h>


const int RAND_SEED = 692;
const int NUMS_SIZE_MIN = 2;
const int NUMS_SIZE_MAX = 20;
const int MAX_NUM = 50;


void build_nums(int ** nums, int * numsSize) {

    int array_size = NUMS_SIZE_MIN + rand() % (NUMS_SIZE_MAX - NUMS_SIZE_MIN + 1);

    // Create the array of integers
    int * nums_array = (int *) malloc(array_size * sizeof(int));
    if (nums_array == NULL) {
        puts("Could not allocate memory for the test array.");
        exit(EXIT_FAILURE);
    }

    // Populate the array with random integers
    for (int i = 0; i < array_size; ++i) {
        nums_array[i] = rand() % (2 * MAX_NUM + 1) - MAX_NUM;
        // Should check that these aren't equal to any of the other numbers...
    }

    // Print the array
    printf("Input array of %d numbers: [", array_size);
    for (int i = 0; i < array_size; ++i) {
        printf("%d", nums_array[i]);
        if (i < array_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // Output the array and array size
    *nums = nums_array;
    *numsSize = array_size;
}


int choose_target(int const nums[], int numsSize) {

    // Choose two elements for the target
    int i = rand() % numsSize;
    int j;
    do {
        // The two indices should be different
        j = rand() % numsSize;
    } while (j == i);

    int num1 = nums[i];
    int num2 = nums[j];
    int target = num1 + num2;

    printf("The selected numbers are %d (index %d) and %d (index %d).\n", num1, i, num2, j);
    printf("The target sum is %d.\n", target);

    return target;
}


void test_two_sum() {
    int * nums;
    int numsSize;
    int target;
    int returnSize;
    int * indices;

    srand(RAND_SEED);
    
    // Create a random array of integers
    build_nums(&nums, &numsSize);

    // Choose the target
    target = choose_target(nums, numsSize);

    printf("\n");

    indices = twoSum(nums, numsSize, target, &returnSize);

    // Assumes that the size of the returned array is 2
    int i = indices[0];
    int j = indices[1];
    int num1 = nums[i];
    int num2 = nums[j];
    printf("The algorithm has selected numbers %d (index %d) and %d (index %d).\n",
        num1, i, num2, j);
    printf("The sum of the two is %d.\n", num1 + num2);

    // Report the results of the test
    if (num1 + num2 == target) {
        printf("The test was successful!\n");
    } else {
        printf("The test failed.\n");
    }

    free(nums);
    free(indices);
}
