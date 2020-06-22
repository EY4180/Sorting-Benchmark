#include "sorting.h"

int get_minrun(int size)
{
	int result = 0;

	for (int bit = log2(size); bit >= 0; --bit)
	{
		if((1 << bit) & size)
		{
			int read_pos = (bit > 5) ? bit - 5 : 0;
			result = size >> read_pos;
			result += (size & (result << read_pos)) < size;
			break;
		}
	}

	return result;
}

int find_next_run(int *arr, int size, int start)
{
	int current_index = start;
	int next_index = start + 1;

	while ((arr[current_index] < arr[next_index]) && next_index < size)
	{
		++current_index;
		++next_index;
	}
	
	return next_index;
}
void tim_sort(int *arr, int size)
{
	int start = 0;
	int end = 0;
	int minrun = get_minrun(size);

	// construct runs in random array
	while (end < size)
	{
		end = find_next_run(arr, size, start);

		if (start + minrun >= size)
		{
			printf("readched end of array, remainder between [%i, %i)\n", start, size);
			t_bin_insert(arr + start, size - start);
			end = size;
		}
		else if (end - start < minrun)
		{
			printf("natural run too low, boost between [%i, %i)\n", start, start + minrun);
			t_bin_insert(arr + start, minrun);
			start = start + minrun;
		}
		else
		{
			printf("natural run of appropriate size, add to stack between [%i, %i)\n", start, end);
			start = end;
		}
	}

	// merge runs in array
}