#include "sorting.h"

void insertion_sort(int *arr, int size)
{
	for (int i = 1; i < size; ++i)
	{
		long key = arr[i];
		int pos = i - 1;

		while (pos >= 0 && (arr[pos] > key))
		{
			arr[pos + 1] = arr[pos];
			--pos;
		}
		arr[pos + 1] = key;
	}
}

void *insertion_bench(void *input)
{
	long *args = input;

	int *arr = malloc(sizeof(int) * args[0]);
	srand(time(0)); // initialize random number generator
	for (int i = 0; i < args[0]; ++i)
		arr[i] = rand() % (1 << args[1]);

	struct timeval stop, start;

	gettimeofday(&start, NULL);
	insertion_sort(arr, args[0]);
	gettimeofday(&stop, NULL);

	free(arr);

	return (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
}