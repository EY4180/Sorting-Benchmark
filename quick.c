#include "sorting.h"

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quick_sort(int *arr, int low, int high)
{
	if (high > low)
	{
		int sorted_pos = low;

		for (int pos = low; pos <= high; ++pos)
			if(arr[pos] < arr[high])
				swap(arr + pos, arr + sorted_pos++);		

		// place pivot in correct position
		swap(arr + high, arr + sorted_pos); 

		// do quicksort on remaining elements to the left and right of pivot
		quick_sort(arr, low, sorted_pos - 1); 
		quick_sort(arr, sorted_pos + 1, high);
	}
}

void *quick_bench(void *input)
{
	long *args = input;
	
	int *arr = malloc(sizeof(int) * args[0]);
	srand(time(0)); // initialize random number generator
	for (int i = 0; i < args[0]; ++i)
		arr[i] = rand() % (1 << args[1]);

	struct timeval stop, start;

	gettimeofday(&start, NULL);
	quick_sort(arr,0 , args[0] - 1); 
	gettimeofday(&stop, NULL);

	free(arr);

	return (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
}