#include "sorting.h"

void selection_sort(int *arr, int size)
{
	for (int element = 0; element < size; ++element)
	{
		int index;
		smallest(arr, size, &index);

		// move smallest element to front of array
		for (int i = index; i > 0 ; --i)
			swap(arr + i, arr + i -1);
	}
}

void t_selection(int *arr, int size)
{
	selection_sort(arr, size);
}