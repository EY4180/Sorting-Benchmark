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

void initialize_benchmark(BENCHMARK_PARAMETERS *param, sort func)
{
	param->func = func;
}

void update_benchmark(BENCHMARK_PARAMETERS *param, int *arr, int size)
{
	param->size = size;
	param->arr = malloc(size * sizeof(*arr));
	memcpy(param->arr, arr, size * sizeof(*arr));
}

void print_benchmark(BENCHMARK_PARAMETERS param)
{
	printf("size : %i\n", param.size);
	print_array(param.arr, param.size);
}

void free_benchmark(BENCHMARK_PARAMETERS *param)
{
	free(param->arr);
}


void print_array(int *arr, int size)
{
	for (int pos = 0; pos < size; ++pos)
		printf("%i ", arr[pos]);

	printf("\n");
}

void fill_random(int *arr, int size, int max)
{
	srand(time(0));

	for (int pos = 0; pos < size; ++pos)
		arr[pos] = rand() % (1 << max);
}