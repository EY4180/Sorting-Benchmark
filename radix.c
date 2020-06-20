#include "sorting.h"

void radix_sort(int *array, int size, int max)
{
	int *counter = malloc(size * sizeof(*counter));
	int *remaining_elements = malloc(size * sizeof(*remaining_elements));

	for (int digit = 0; digit < max; ++digit)
	{
		long left_position = 0;
		long remainder = 0;

		for (long element = 0; element < size; ++element)
		{
			if ((1 << digit) & array[element])
				counter[left_position++] = array[element];
			else
				remaining_elements[remainder++] = array[element];
		}

		memmove(array, counter, left_position * sizeof(int));
		memmove(array + left_position, remaining_elements, remainder * sizeof(int));
	}

	free(remaining_elements);
	free(counter);
}

void *radix_bench(void *input)
{
	long *args = input;
	
	int *arr = malloc(sizeof(int) * args[0]);
	srand(time(0)); // initialize random number generator
	for (int i = 0; i < args[0]; ++i)
		arr[i] = rand() % (1 << args[1]);

	struct timeval stop, start;

	gettimeofday(&start, NULL);
	radix_sort(arr, args[0], args[1]); // begin radix sort with array of length n
	gettimeofday(&stop, NULL);

	free(arr);

	return (void *) ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}