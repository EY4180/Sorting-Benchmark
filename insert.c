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

void bin_insertion_sort(int *arr, int size)
{
	for (int i = 1; i < size; ++i)
	{
		long key = arr[i];
		insert_into_array(arr, i, key);
	}
}

void t_insert(int *arr, int size)
{
	insertion_sort(arr, size);
}

void t_bin_insert(int *arr, int size)
{
	bin_insertion_sort(arr, size);
}