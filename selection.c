#include "sorting.h"

void selection_sort(int *arr, int size)
{
	for (int element = 0; element < size; ++element)
	{
		int index;
		smallest(arr, element, size - 1, &index);
		
		// move smallest element to front of array
		swap(&arr[element], &arr[index]);
	}
}

void t_selection(int *arr, int size)
{
	selection_sort(arr, size);
}