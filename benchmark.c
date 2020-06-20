#pragma GCC optimize("Ofast")

#include "sorting.h"
#include <pthread.h>

#define MAX_VALUE 16
#define MAX_THREADS 8
#define DATA_FILE "data.dat"
#define GRAPH_FILE "graph.txt"
#define MAX_DATA_POINTS (1 << 6)
#define ITERATION_MULTIPLIER (1 << 6)

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

int main(int argc, char const *argv[])
{
	bench func[] = {&merge_bench, &radix_bench, &insertion_bench, &bubble_bench, &quick_bench, &shell_bench};
	int total_benchmarks = sizeof(func) / sizeof(*func);

	pthread_t threads[total_benchmarks];

	long **simulation_times = (long **)malloc(sizeof(long *) * MAX_DATA_POINTS);
	for (int i = 0; i < MAX_DATA_POINTS; ++i)
		simulation_times[i] = (long *)malloc(sizeof(long) * total_benchmarks);

	for (long iteration = 0; iteration < MAX_DATA_POINTS; ++iteration)
	{
		// start threads
		for (int n = 0; n < total_benchmarks; ++n)
		{
			long args[] = {iteration * ITERATION_MULTIPLIER, MAX_VALUE};
			pthread_create(&threads[n], NULL, func[n], (void *)args);
		}

		// close threads
		for (long n = 0; n < total_benchmarks; ++n)
		{
			long result;
			pthread_join(threads[n], (void **)&result);
			simulation_times[iteration][n] = result;
		}

		printf("iteration %li complete\n", iteration);
	}

	update_data_file(simulation_times, MAX_DATA_POINTS, total_benchmarks);
	init_gnuplot();

	free(simulation_times);

	return 0;
}
