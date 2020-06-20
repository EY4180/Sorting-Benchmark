#include "sorting.h"

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

void t_quick(int *arr, int size)
{
	quick_sort(arr, 0, size - 1);
}