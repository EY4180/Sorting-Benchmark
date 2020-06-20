#include "sorting.h"

void merge_sort(int *arr, int start, int end)
{
    if (start < end)
    {
        long midpoint = (start + end) / 2;
        merge_sort(arr, start, midpoint);
        merge_sort(arr, midpoint + 1, end);

        long left_size = midpoint - start + 1;
        long right_size = end - midpoint;

        int *left = malloc(sizeof(int) * left_size);
        int *right = malloc(sizeof(int) * right_size);

        memcpy(left, arr + start, left_size * sizeof(int));
        memcpy(right, arr + midpoint + 1, right_size * sizeof(int));

        long left_position = 0;
        long right_position = 0;
        for (long index = start; index <= end; ++index)
        {
            char left_empty = left_position == left_size;
            char add_left = (right_position == right_size) || (left[left_position] < right[right_position]);

            if (left_empty)
				arr[index] = right[right_position++];
            else if (add_left)
                arr[index] = left[left_position++];
            else
                arr[index] = right[right_position++];
        }

		free(left);
		free(right);
    }
}

void t_merge(int *arr, int size)
{
	merge_sort(arr, 0, size - 1);
}