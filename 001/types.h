#ifndef TYPES_H
#define TYPES_H

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

// typedef int * (*Algorithm)(NumsArray, Target, int *);
typedef int * (*Algorithm)(int *, int, int, int *);

#endif