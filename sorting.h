#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

typedef void* (*bench)(void*);

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