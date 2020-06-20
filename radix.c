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

void t_radix(int *arr, int size)
{
	int max = largest(arr, size);
	radix_sort(arr, size, max);
}