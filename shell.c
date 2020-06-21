#include "sorting.h"

void shell_sort(int *arr, int size)
{
	for (int gap = size / 2; gap > 0; gap /= 2)
		for (int element = 0; element < size - gap; ++element)
			for (int sub_element = 0; sub_element < size - gap; sub_element += gap)
				if (arr[sub_element + gap] > arr[sub_element])
					swap(&arr[sub_element + gap], &arr[sub_element]);
}

void t_shell(int *arr, int size)
{
	shell_sort(arr, size);
}
