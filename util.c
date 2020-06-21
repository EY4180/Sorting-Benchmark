#include "sorting.h"

int largest(int *arr, int size)
{
    int number = *arr;
    for (int pos = 1; pos < size; ++pos)
		if (arr[pos] > number)
			number = arr[pos];
	
    return ceil(log2(number));
}

int smallest(int *arr, int start, int end, int *index)
{
    int number = arr[start];
	*index = start;
    for (int pos = start + 1; pos <= end; ++pos)
		if (arr[pos] < number)
		{
			number = arr[pos];
			*index = pos;
		}

    return number;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void *benchmark(void *args)
{
    BENCHMARK_PARAMETERS *param = args;

	struct timeval stop, start;

	gettimeofday(&start, NULL);
    param->func(param->arr, param->size);
	gettimeofday(&stop, NULL);

	return (void *) (intptr_t) ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}