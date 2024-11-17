#include "two-sum.c"

#include <stdlib.h>


const int RAND_SEED = 692;
const int NUMS_SIZE_MIN = 2;
const int NUMS_SIZE_MAX = 20;
const int MAX_NUM = 50;


typedef struct {
    int * array;
    int size;
} NumsArray;

typedef struct {
    int i;
    int j;
    int num1;
    int num2;
    int sum;
} Target;


NumsArray build_nums() {

    NumsArray nums; 

    // Randomly select the array size
    nums.size = NUMS_SIZE_MIN + rand() % (NUMS_SIZE_MAX - NUMS_SIZE_MIN + 1);

    // Create the array of integers
    nums.array = (int *) malloc(nums.size * sizeof(int));
    if (nums.array == NULL) {
        puts("Could not allocate memory for the test array.");
        exit(EXIT_FAILURE);
    }

    // Populate the array with random integers
    for (int i = 0; i < nums.size; ++i) {
        nums.array[i] = rand() % (2 * MAX_NUM + 1) - MAX_NUM;
        // Should check that these aren't equal to any of the other numbers...
    }

    return nums;
}


void free_nums(NumsArray * nums) {
    free(nums->array);
    nums->array = NULL;
    nums->size = 0;
}


Target choose_target(const NumsArray nums) {

    // Choose two elements for the target
    int i = rand() % (nums.size - 1);
    int j = (i + 1) + rand() % (nums.size - (i + 1));

    int num1 = nums.array[i];
    int num2 = nums.array[j];
    int sum = num1 + num2;

    Target target = {
        .i = i,
        .j = j,
        .num1 = num1,
        .num2 = num2,
        .sum = sum
    };

    return target;
}


void print_sampling(const NumsArray nums, const Target target) {

    // Print the array
    printf("Input array of %d numbers: [", nums.size);
    for (int i = 0; i < nums.size; ++i) {
        printf("%d", nums.array[i]);
        if (i < nums.size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // Print the target
    printf("The selected numbers are %d (index %d) and %d (index %d).\n",
        target.num1, target.i, target.num2, target.j);
    printf("The target sum is %d.\n", target.sum);

    printf("\n");
}


void test_two_sum() {

    srand(RAND_SEED);
    
    // Create a random array of integers and the target, and print the results
    NumsArray nums = build_nums();
    Target target = choose_target(nums);
    print_sampling(nums, target);

    // Find two numbers that sum to the target
    int returnSize;
    int * indices = twoSum(nums.array, nums.size, target.sum, &returnSize);

    // Assumes that the size of the returned array is 2
    int i = indices[0];
    int j = indices[1];
    int num1 = nums.array[i];
    int num2 = nums.array[j];
    int sum = num1 + num2;
    printf("The algorithm has selected numbers %d (index %d) and %d (index %d).\n",
        num1, i, num2, j);
    printf("The sum of the two is %d.\n", sum);

    // Report the results of the test
    if (sum == target.sum) {
        printf("The test was successful!\n");
    } else {
        printf("The test failed.\n");
    }

    // Free all allocated memory
    free_nums(&nums);
    free(indices);
}
