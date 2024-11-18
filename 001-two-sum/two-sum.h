#ifndef __TWO_SUM_H__
#define __TWO_SUM_H__

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

typedef int * (*Algorithm)(NumsArray, Target, int *);

#endif