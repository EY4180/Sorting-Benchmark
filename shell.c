#include <sorting.h>

void shell_sort(int *arr, int size)
{
	for (int gap = size/2; gap > 0; gap /= 2)
		for (int element = 0; element < size - gap; ++element)
			for (int sub_element = 0; sub_element < size - gap; sub_element += gap)
				if (arr[sub_element + gap] > arr[sub_element])
					swap(arr + sub_element + gap, arr + sub_element);
}


void shell_bench(void *input)
{
	long *args = input;
	
	int *arr = malloc(sizeof(int) * args[0]);
	srand(time(0)); // initialize random number generator
	for (int i = 0; i < args[0]; ++i)
		arr[i] = rand() % (1 << args[1]);

	struct timeval stop, start;

	gettimeofday(&start, NULL);
	shell_sort(arr, args[0]); // begin radix sort with array of length n
	gettimeofday(&stop, NULL);

	free(arr);

	return (void *) ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}