#include "sorting.h"

const int X = 0;
const int Y = 1;
const int Z = 2;

typedef struct run
{
	int *start;
	int size;
} RUN;

void merge_runs(RUN **run_list, int *arr)
{	
	// do while the number of runs is more than 1
	// probably keep track of the number of runs in the list

	// merge runs Y with X or Z (whichever one is smaller)
	if(run_list[Z]->size <= run_list[Y]->size + run_list[X]->size || run_list[Y]->size <= run_list[X]->size)
	{
		// merge Z and Y
		if(run_list[X]->size > run_list[Z]->size)
		{
			// run merge between Z and Y arrays

			// merge runs Z and Y
		}
		// merge X and Y
		else
		{
			// run merge between X and Y arrays

			// merge runs X and Y
			*run_list[X] = *run_list[Y];			
		}
		
	}
}

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

	// construct runs in array
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