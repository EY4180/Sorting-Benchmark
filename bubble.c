#include "sorting.h"

void bubble_sort(int *arr, int size)
{
	int total_swaps, pos;
	do
	{
		pos = 0;
		total_swaps = 0;

		while ((pos + 1) < size)
		{
			if (arr[pos] > arr[pos + 1])
			{
				int temp = arr[pos + 1];
				arr[pos + 1] = arr[pos];
				arr[pos] = temp;
				++total_swaps;	
			}
			
			++pos;
		}
	} while (total_swaps > 0);
}

void *bubble_bench(void *input)
{
	long *args = input;

	int *arr = malloc(sizeof(int) * args[0]);
	srand(time(0)); // initialize random number generator
	for (int i = 0; i < args[0]; ++i)
		arr[i] = rand() % (1 << args[1]);

	struct timeval stop, start;

	gettimeofday(&start, NULL);
	bubble_sort(arr, args[0]); // begin merge sort with array of length n
	gettimeofday(&stop, NULL);

	free(arr);

	return (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
}
