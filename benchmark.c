#pragma GCC optimize("Ofast")

#include "sorting.h"
#include <pthread.h>

#define MAX_VALUE 16
#define MAX_THREADS 8
#define DATA_FILE "data.dat"
#define GRAPH_FILE "graph.txt"
#define MAX_DATA_POINTS (1 << 8)
#define ITERATION_MULTIPLIER (1 << 8)

void update_data_file(long **results, int iterations, int tests)
{
	FILE *data = fopen(DATA_FILE, "w");

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

void print_array(int *arr, int size)
{
	for (int pos = 0; pos < size; ++pos)
		printf("%i ", arr[pos]);

	printf("\n");
}

void initialize_benchmark(BENCHMARK_PARAMETERS *param, sort func)
{
	param->func = func;
}

void update_benchmark(BENCHMARK_PARAMETERS *param, int *arr, int size)
{
	param->size = size;
	param->arr = malloc(size * sizeof(*arr));
	memcpy(param->arr, arr, size * sizeof(*arr));
}

void print_benchmark(BENCHMARK_PARAMETERS param)
{
	printf("size : %i\n", param.size);
	print_array(param.arr, param.size);
}

void free_benchmark(BENCHMARK_PARAMETERS *param)
{
	free(param->arr);
}

void fill_random(int *arr, int size, int max)
{
	srand(time(0));

	for (int pos = 0; pos < size; ++pos)
		arr[pos] = rand() % (1 << max);
}

int main(int argc, char const *argv[])
{
	sort funcs[] = {&t_merge, &t_radix, &t_insert, &t_bubble, &t_quick, &t_shell};
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

	return EXIT_SUCCESS;
}
