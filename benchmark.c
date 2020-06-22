#pragma GCC optimize("Ofast")

#include "sorting.h"
#include <pthread.h>

#define DATA_FILE "data.dat"
#define GRAPH_FILE "graph.txt"
#define DATA_HEADERS "Size Merge Radix Insert Selection Bubble Quick Shell Bin"

#define MAX_VALUE 16
#define MAX_DATA_POINTS (1 << 6)
#define ITERATION_MULTIPLIER (1 << 8)

void update_data_file(long **results, int iterations, int tests)
{
	FILE *data = fopen(DATA_FILE, "w");

	fprintf(data, "%s\n", DATA_HEADERS);

	for (int i = 0; i < iterations; ++i)
	{
		fprintf(data, "%i ", i);
		for (int n = 0; n < tests; ++n)
		{
			fprintf(data, "%li ", results[i][n]);
		}
		fprintf(data, "\n");
	}

	fclose(data);
}

void init_gnuplot()
{
	FILE *settings = fopen(GRAPH_FILE, "r");
	FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), settings) != NULL)
	{
		fprintf(gnuplotPipe, buffer);
	}

	fclose(settings);
	fclose(gnuplotPipe);
}

int main(int argc, char const *argv[])
{
	sort funcs[] = {&t_merge, &t_radix, &t_insert, &t_selection, &t_bubble, &t_quick, 
					&t_shell, &t_bin_insert};

	int total_tests = sizeof(funcs) / sizeof(*funcs);
	pthread_t threads[total_tests];
	BENCHMARK_PARAMETERS params[total_tests];

	for (int test = 0; test < total_tests; ++test)
		initialize_benchmark(&params[test], funcs[test]);

	long **simulation_times = (long **)malloc(sizeof(long *) * MAX_DATA_POINTS);
	for (int i = 0; i < MAX_DATA_POINTS; ++i)
		simulation_times[i] = (long *)malloc(sizeof(long) * total_tests);

	for (long iteration = 0; iteration < MAX_DATA_POINTS; ++iteration)
	{
		int size = iteration * ITERATION_MULTIPLIER;
		int *arr = malloc(size * sizeof(*arr));
		fill_random(arr, size, MAX_VALUE);

		// start threads with random array
		for (int test = 0; test < total_tests; ++test)
		{
			update_benchmark(&params[test], arr, size);
			pthread_create(&threads[test], NULL, benchmark, (void *)&params[test]);
		}

		// close threads and return results
		for (int test = 0; test < total_tests; ++test)
		{
			long result;
			pthread_join(threads[test], (void **)&result);
			simulation_times[iteration][test] = result;
			free_benchmark(&params[test]);
		}

		free(arr);
		printf("iteration %li complete\n", iteration);
	}

	update_data_file(simulation_times, MAX_DATA_POINTS, total_tests);
	init_gnuplot();

	free(simulation_times);
	

	/*
	int size = 20;
	int *arr = malloc(size * sizeof(*arr));
	fill_random(arr, size, 7);
	print_array(arr, size);
	t_bin_insert(arr, size);
	print_array(arr, size);
	printf("%i \n", binary_search(arr, size, 100));
	getchar();
	*/
	return EXIT_SUCCESS;
}
