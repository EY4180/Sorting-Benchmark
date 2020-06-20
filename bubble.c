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
				swap(arr + pos, arr + pos + 1);
				++total_swaps;	
			}
			
			++pos;
		}
	} while (total_swaps > 0);
}

void t_bubble(int *arr, int size)
{
	bubble_sort(arr, size);
}