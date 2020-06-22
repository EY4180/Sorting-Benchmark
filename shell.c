#include "sorting.h"

void shell_sort(int *arr, int size)
{
	for (int k = log2(size + 1); k > 0; --k)
	{
		int gap = (1 << k) - 1;
		for (int element = 0; element < gap; ++element)
		{
			for (int i = element + gap; i < size; i += gap)
			{
				long key = arr[i];
				int pos = i - gap;

				while (pos >= element && (arr[pos] > key))
				{
					arr[pos + gap] = arr[pos];
					pos -= gap;
				}
				arr[pos + gap] = key;
			}
		}
	}
}

void t_shell(int *arr, int size)
{
	shell_sort(arr, size);
}
