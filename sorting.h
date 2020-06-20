#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef void* (*bench)(void*);
typedef void (*sort)(int *arr, int size);

typedef struct benchmark_parameters 
{
    int size;
    int *arr;
    sort func;
} BENCHMARK_PARAMETERS;

extern void radix_sort(int *array, int size, int max);
extern void *radix_bench(void *args);

extern int merge_sort(int *arr, int start, int end);
extern void *merge_bench(void *input);

extern void insertion_sort(int *arr, int size);
extern void *insertion_bench(void *input);

extern void bubble_sort(int *arr, int size);
extern void *bubble_bench(void *input);

extern void quick_sort(int *arr, int low, int high);
extern void *quick_bench(void *input);

extern void swap(int *a, int *b);

extern void shell_sort(int *arr, int size);
extern void *shell_bench(void *input);