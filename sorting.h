#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef void (*sort)(int *arr, int size);

typedef struct benchmark_parameters 
{
    int size;
    int *arr;
    sort func;
} BENCHMARK_PARAMETERS;

extern void radix_sort(int *array, int size, int max);
extern void t_radix(int *arr, int size);

extern void merge_sort(int *arr, int start, int end);
extern void t_merge(int *arr, int size);

extern void insertion_sort(int *arr, int size);
extern void t_insert(int *arr, int size);

extern void bubble_sort(int *arr, int size);
extern void t_bubble(int *arr, int size);

extern void quick_sort(int *arr, int low, int high);
extern void t_quick(int *arr, int size);

extern void shell_sort(int *arr, int size);
extern void t_shell(int *arr, int size);

extern void selection_sort(int *arr, int size);
extern void t_selection(int *arr, int size);


extern void swap(int *a, int *b);
extern int largest(int *arr, int size);
extern void *benchmark(void *args);
extern int smallest(int *arr, int start, int end, int *index);
extern void initialize_benchmark(BENCHMARK_PARAMETERS *param, sort func);
extern void update_benchmark(BENCHMARK_PARAMETERS *param, int *arr, int size);
extern void print_benchmark(BENCHMARK_PARAMETERS param);
extern void free_benchmark(BENCHMARK_PARAMETERS *param);
extern void print_array(int *arr, int size);
extern void fill_random(int *arr, int size, int max);